/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/12 21:38:28 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_ul	updated_runtime(t_data *data)
{
	set_timer(&data->uptime,
		update_time(OP_MSEC, data) - data->epoch,
		&data->mutex[MX_EPCH], data);
	return (get_timer(&data->uptime, &data->mutex[MX_EPCH], data));
}

static inline void	set_finished(t_data *data)
{
	set_status(&data->stat[ST_DONE], true, &data->mutex[MX_DONE], data);
}

static bool	philosophers_full(t_data *data)
{
	t_philo	*phil;
	int		done;
	int		i;

	i = -1;
	done = 0;
	while (++i < data->input->philos)
	{
		phil = data->phils + i;
		if (get_status(&phil->stat[ST_FULL], &phil->mutex[MX_FULL], data))
			done++;
	}
	if (done == data->input->philos)
		return (true);
	return (false);
}

static bool	philosopher_death(t_data *data)
{
	t_ul	mealtime;
	t_philo	*phil;
	int		i;

	i = -1;
	while (++i < data->input->philos)
	{
		phil = data->phils + i;
		if (get_status(&phil->stat[ST_EAT], &phil->mutex[MX_EAT], data))
			continue ;
		mealtime = get_timer(&phil->mealtime, &phil->mutex[MX_TIME], data);
		if (updated_runtime(data) - mealtime > (t_ul)data->input->die)
		{
			set_status(&phil->stat[ST_DIE], true, &phil->mutex[MX_DIE], data);
			log_status(phil, ST_DIE);
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
