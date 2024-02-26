/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/26 19:21:18 by jmertane         ###   ########.fr       */
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
	log_status(phil, ST_EAT);
	phil->meals -= 1;
	percision_sleep(data->input->eat, data);
	operate_mutex(phil->f1, OP_UNLOCK, data);
	operate_mutex(phil->f2, OP_UNLOCK, data);
}

void	*process_monitor(void *param)
{
	t_philo	*phil;

	phil = (t_philo *)param;
	spinlock_threads(phil->data);
	while (!process_finished(phil->data)
		&& !process_error(phil->data))
	{
		eat_routine(phil, phil->data);
		sleep_routine(phil, phil->data);
	}
	return (NULL);
}
