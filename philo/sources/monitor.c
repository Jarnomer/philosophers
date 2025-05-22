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

static bool	philosophers_full(t_data *data)
{
	t_philo	*philo;
	int		finished_philos;
	int		philo_count;
	int		i;

	i = 0;
	finished_philos = 0;
	philo_count = data->input->philo_count;
	if (data->input->meals_count < 0)
		return (false);
	while (i < philo_count)
	{
		philo = data->philos + i++;
		if (get_status(&philo->stat[ST_FULL], &philo->mutex[MX_FULL], data))
			finished_philos++;
		if (finished_philos + (philo_count - i) < philo_count)
			return (false);
	}
	return (finished_philos == philo_count);
}

static bool	philosopher_death(t_data *data, long current_time)
{
	long	mealtime;
	long	time_to_die;
	t_philo	*philo;
	int		i;

	i = 0;
	time_to_die = (long)data->input->time_to_die;
	while (i < data->input->philo_count)
	{
		philo = data->philos + i++;
		mealtime = get_timer(&philo->mealtime, &philo->mutex[MX_TIME], data);
		if (current_time - mealtime > time_to_die)
		{
			log_status(philo, ST_DIE);
			return (true);
		}
	}
	return (false);
}

void	*run_monitor(void *param)
{
	t_data	*data;
	long	current_time;

	data = (t_data *)param;
	threads_spinlocked(data);
	while (true)
	{
		if (process_finished(data) || process_failed(data))
			break ;
		current_time = operate_timer(OP_MSEC, data) - data->epoch;
		set_timer(&data->uptime, current_time, &data->mutex[MX_EPCH], data);
		if (philosopher_death(data, current_time) || philosophers_full(data))
			set_finished(data);
		usleep(500);
	}
	return (NULL);
}
