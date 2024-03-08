/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/08 14:23:44 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	set_finished(t_data *data)
{
	set_status(&data->stat[ST_DONE], true, &data->mutex[MX_DONE], data);
}

static inline bool	philosopher_full(t_philo *phil, t_data *data)
{
	return (get_status(&phil->stat[ST_FULL], &phil->mutex[MX_FULL], data));
}

static bool	philosopher_death(t_philo *phil, t_data *data)
{
	t_ul	mealtime;

	mealtime = get_timer(&phil->mealtime, &phil->mutex[MX_TIME], data);
	if (data->uptime - mealtime > (t_ul)data->input->die)
	{
		log_status(phil, ST_DIE);
		return (true);
	}
	return (false);
}

void	*process_monitor(void *param)
{
	t_data	*data;
	t_philo	*phil;
	int		i;

	data = (t_data *)param;
	threads_spinlocked(data);
	while (true)
	{
		i = 0;
		while (i < data->input->philos)
		{
			phil = data->phils + i++;
			set_timer(&data->uptime,
				update_time(OP_MSEC, data) - data->epoch,
				&data->mutex[MX_EPCH], data);
			if (process_finished(data)
				|| process_failed(data))
				return (NULL);
			else if (philosopher_full(phil, data)
				|| philosopher_death(phil, data))
				set_finished(data);
		}
	}
	return (NULL);
}
