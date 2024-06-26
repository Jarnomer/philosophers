/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/01 14:56:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*process_loner(void *param)
{
	t_philo	*phil;
	t_data	*data;

	phil = (t_philo *)param;
	data = phil->data;
	threads_spinlocked(data);
	log_status(phil, ST_TAKE);
	percision_sleep(data->input->die, data);
	while (true)
		if (process_finished(data)
			|| process_failed(data))
			break ;
	return (NULL);
}

static void	sleep_routine(t_philo *phil, t_data *data)
{
	log_status(phil, ST_SLP);
	percision_sleep(data->input->sleep, data);
	log_status(phil, ST_THK);
	percision_sleep(phil->cooldown, data);
}

static void	handle_forks(t_philo *phil, t_state state, t_data *data)
{
	if (state == ST_TAKE)
	{
		operate_mutex(phil->f1, OP_LOCK, data);
		log_status(phil, ST_TAKE);
		operate_mutex(phil->f2, OP_LOCK, data);
		log_status(phil, ST_TAKE);
	}
	else if (state == ST_PUT)
	{
		operate_mutex(phil->f1, OP_UNLOCK, data);
		operate_mutex(phil->f2, OP_UNLOCK, data);
	}
	else
	{
		log_error(FAILURE, MSG_STAT, "<handle_forks>", "");
		error_occured(data, EXIT_FAILURE);
	}
}

static void	eat_routine(t_philo *phil, t_data *data)
{
	handle_forks(phil, ST_TAKE, data);
	set_timer(&phil->mealtime,
		update_time(OP_MSEC, data) - data->epoch,
		&phil->mutex[MX_TIME], data);
	log_status(phil, ST_EAT);
	percision_sleep(data->input->eat, data);
	handle_forks(phil, ST_PUT, data);
	if (--phil->meals == 0)
		set_status(&phil->stat[ST_FULL], true,
			&phil->mutex[MX_FULL], data);
}

void	*process_routine(void *param)
{
	t_philo	*phil;
	t_data	*data;

	phil = (t_philo *)param;
	data = phil->data;
	threads_spinlocked(data);
	if (!phil->stat[ST_LEAD])
	{
		log_status(phil, ST_THK);
		usleep(500);
	}
	while (true)
	{
		if (process_finished(data)
			|| process_failed(data))
			break ;
		eat_routine(phil, data);
		sleep_routine(phil, data);
	}
	return (NULL);
}
