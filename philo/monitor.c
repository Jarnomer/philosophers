/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/27 16:32:28 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	set_finished(t_philo *phil, t_data *data, t_state state)
{
	if (state == ST_DIE)
		log_status(phil, ST_DIE);
	set_status(&data->mutex[MX_DONE],
		&data->stat[ST_DONE], true, data);
}

static void	check_full(t_data *data)
{
	t_philo	*phil;
	int		i;

	i = 0;
	while (i < data->input->philos)
	{
		phil = data->phils + i++;
		if (get_status(&phil->mutex[MX_FULL],
				&phil->stat[ST_FULL], data))
			set_finished(phil, data, ST_FULL);
	}
}

static void	check_time(t_data *data)
{
	t_philo	*phil;
	t_ul	uptime;
	t_ul	mealtime;
	int		i;

	i = 0;
	while (i < data->input->philos)
	{
		phil = data->phils + i++;
		mealtime = get_timer(&phil->mutex[MX_TIME], &phil->timer, data);
		uptime = update_time(OP_MSEC, data) - data->start;
		if (uptime - mealtime > (t_ul)data->input->die
			&& !get_status(&phil->mutex[MX_EAT],
				&phil->stat[ST_EAT], data))
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
		check_time(data);
		check_full(data);
	}
	return (NULL);
}
