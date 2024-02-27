/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/27 18:12:28 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep_routine(t_philo *phil, t_data *data)
{
	log_status(phil, ST_SLEEP);
	percision_sleep(data->input->sleep, data);
	log_status(phil, ST_THINK);
}

static void	manage_forks(t_philo *phil, t_data *data, bool take)
{
	if (take == true)
	{
		operate_mutex(phil->f1, OP_LOCK, data);
		log_status(phil, ST_TAKE);
		operate_mutex(phil->f2, OP_LOCK, data);
		log_status(phil, ST_TAKE);
	}
	else
	{
		operate_mutex(phil->f1, OP_UNLOCK, data);
		operate_mutex(phil->f2, OP_UNLOCK, data);
	}
}

static void	eat_routine(t_philo *phil, t_data *data)
{
	manage_forks(phil, data, true);
	set_status(&data->mutex[MX_EAT],
		&phil->stat[ST_EAT], true, data);
	log_status(phil, ST_EAT);
	percision_sleep(data->input->eat, data);
	phil->meals -= 1;
	set_status(&data->mutex[MX_EAT],
		&phil->stat[ST_EAT], false, data);
	set_timer(&data->mutex[MX_DINE], &phil->timer,
		update_time(OP_MSEC, data), data);
	manage_forks(phil, data, false);
}

void	*process_routine(void *param)
{
	t_philo	*phil;
	t_data	*data;

	phil = (t_philo *)param;
	data = phil->data;
	threads_spinlocked(data);
	while (true)
	{
		if (process_finished(data)
			|| process_failed(data))
			break ;
		eat_routine(phil, data);
		if (!phil->meals)
			set_status(&data->mutex[MX_FULL],
				&phil->stat[ST_FULL], true, data);
		sleep_routine(phil, data);
	}
	return (NULL);
}
