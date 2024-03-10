/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/08 15:26:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	set_finished(t_data *data)
{
	set_status(&data->stat[ST_DONE], true, &data->mutex[MX_DONE], data);
}

static bool	philosophers_full(t_data *data)
{
	t_philo	*phil;
	int		fulls;
	int		i;

	fulls = 0;
	i = 0;
	while (i < data->input->philos)
	{
		phil = data->phils + i++;
		if (get_status(&phil->stat[ST_FULL], &phil->mutex[MX_FULL], data))
			fulls++;
	}
	if (fulls == data->input->philos)
		return (true);
	return (false);
}

static bool	philosopher_death(t_philo *phil, t_data *data)
{
	t_ul	mealtime;
	t_ul	uptime;

	if (get_status(&phil->stat[ST_EAT], &phil->mutex[MX_EAT], data))
		return (false);
	mealtime = get_timer(&phil->mealtime, &phil->mutex[MX_TIME], data);
	uptime = get_timer(&data->uptime, &data->mutex[MX_EPCH], data);
	if (uptime - mealtime > (t_ul)data->input->die)
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
			else if (philosopher_death(phil, data)
				|| philosophers_full(data))
				set_finished(data);
		}
	}
	return (NULL);
}
