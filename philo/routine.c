/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/04 17:33:05 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep_routine(t_philo *phil, t_data *data)
{
	log_status(phil, ST_SLP);
	percision_sleep(data->input->sleep, data);
	log_status(phil, ST_THK);
}

static void	put_forks(t_philo *phil, t_data *data)
{
	operate_mutex(phil->f1, OP_UNLOCK, data);
	operate_mutex(phil->f2, OP_UNLOCK, data);
}

static void	take_forks(t_philo *phil, t_data *data)
{
	operate_mutex(phil->f1, OP_LOCK, data);
	log_status(phil, ST_TAKE);
	operate_mutex(phil->f2, OP_LOCK, data);
	log_status(phil, ST_TAKE);
}

static void	eat_routine(t_philo *phil, t_data *data)
{
	take_forks(phil, data);
	set_status(&phil->stat[ST_EAT], true, &phil->mutex[MX_EAT], data);
	log_status(phil, ST_EAT);
	percision_sleep(data->input->eat, data);
	phil->meals -= 1;
	set_status(&phil->stat[ST_EAT], false, &phil->mutex[MX_EAT], data);
	set_timer(&phil->timer, update_time(OP_MSEC, data) - data->epoch,
		&phil->mutex[MX_TIME], data);
	put_forks(phil, data);
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
			set_status(&phil->stat[ST_FULL], true,
				&phil->mutex[MX_FULL], data);
		sleep_routine(phil, data);
	}
	return (NULL);
}
