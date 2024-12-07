/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/30 20:04:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	refresh_uptime(t_data *data)
{
	set_timer(&data->uptime, operate_timer(OP_MSEC, data) - data->epoch,
		&data->mutex[MX_EPCH], data);
	return (get_timer(&data->uptime, &data->mutex[MX_EPCH], data));
}

static bool	philosophers_full(t_data *data)
{
	t_philo	*philo;
	int		finished_philos;
	int		i;

	i = 0;
	finished_philos = 0;
	while (i < data->input->philo_count)
	{
		philo = data->philos + i++;
		if (get_status(&philo->stat[ST_FULL], &philo->mutex[MX_FULL], data))
			finished_philos++;
	}
	if (finished_philos == data->input->philo_count)
		return (true);
	return (false);
}

static bool	philosopher_death(t_data *data)
{
	long	mealtime;
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->input->philo_count)
	{
		philo = data->philos + i++;
		mealtime = get_timer(&philo->mealtime, &philo->mutex[MX_TIME], data);
		if (refresh_uptime(data) - mealtime > (long)data->input->time_to_die)
		{
			log_status(philo, ST_DIE);
			return (true);
		}
	}
	return (false);
}

void	*process_monitor(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	threads_spinlocked(data);
	while (true)
	{
		if (process_finished(data)
			|| process_failed(data))
			break ;
		else if (philosopher_death(data)
			|| philosophers_full(data))
			set_finished(data);
	}
	return (NULL);
}
