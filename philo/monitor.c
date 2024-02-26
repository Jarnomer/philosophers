/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/26 08:14:34 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep_routine(t_philo *phil, t_data *data)
{
	log_status(phil, ST_SLEEP);
	percision_sleep(data->input->sleep, data);
	log_status(phil, ST_THINK);
}

static void	eat_routine(t_philo *phil, t_data *data)
{
	operate_mutex(phil->f1, OP_LOCK, data);
	log_status(phil, ST_TAKE);
	operate_mutex(phil->f2, OP_LOCK, data);
	log_status(phil, ST_TAKE);
	log_status(phil, ST_EATING);
	phil->meals -= 1;
	percision_sleep(data->input->eat, data);
	operate_mutex(phil->f1, OP_UNLOCK, data);
	operate_mutex(phil->f2, OP_UNLOCK, data);
}

void	*process_monitor(void *param)
{
	t_philo	*phil;
	t_data	*data;

	phil = (t_philo *)param;
	data = phil->data;
	spinlock_threads(data);
	while (!process_finished(data)
		&& !process_error(data))
	{
		// mutate_timer(&data->mutex[MX_TIME], &data->start,
		// 	update_timer(OP_MSEC, data) - data->start, data);
		eat_routine(phil, data);
		sleep_routine(phil, data);
		// break ;
	}
	return (NULL);
}
