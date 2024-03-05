/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/04 21:16:28 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	set_finished(t_philo *phil, t_data *data, t_state state)
{
	if (state == ST_DIE)
		log_status(phil, ST_DIE);
	set_status(&data->stat[ST_DONE], true, &data->mutex[MX_DONE], data);
}

static void	status_checker(t_data *data)
{
	t_philo	*phil;
	t_ul	uptime;
	t_ul	mealtime;
	int		i;

	i = 0;
	while (i < data->input->philos)
	{
		phil = data->phils + i++;
		if (process_finished(data) || process_failed(data))
			return ;
		mealtime = get_timer(&phil->timer, &phil->mutex[MX_TIME], data);
		uptime = update_time(OP_MSEC, data) - data->start;
		if (get_status(&phil->stat[ST_FULL], &phil->mutex[MX_FULL], data))
			set_finished(phil, data, ST_FULL);
		else if (uptime - mealtime > (t_ul)data->input->die)
			set_finished(phil, data, ST_DIE);
	}
}

void	*process_monitor(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (true)
	{
		if (process_finished(data)
			|| process_failed(data))
			break ;
		status_checker(data);
	}
	return (NULL);
}
