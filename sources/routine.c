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

#include <philo.h>

void	*process_loner(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	threads_spinlocked(data);
	log_status(philo, ST_TAKE);
	percision_sleep(data->input->time_to_die, data);
	while (true)
		if (process_finished(data)
			|| process_failed(data))
			break ;
	return (NULL);
}

static void	sleep_routine(t_philo *philo, t_data *data)
{
	log_status(philo, ST_SLP);
	percision_sleep(data->input->time_to_sleep, data);
	log_status(philo, ST_THK);
	percision_sleep(1, data);
}

static void	handle_forks(t_philo *philo, t_state state, t_data *data)
{
	if (state == ST_TAKE)
	{
		operate_mutex(philo->f1, OP_LOCK, data);
		log_status(philo, ST_TAKE);
		operate_mutex(philo->f2, OP_LOCK, data);
		log_status(philo, ST_TAKE);
	}
	else if (state == ST_PUT)
	{
		operate_mutex(philo->f1, OP_UNLOCK, data);
		operate_mutex(philo->f2, OP_UNLOCK, data);
	}
	else
	{
		log_error(ERR_STAT, MSG_STAT, "<handle_forks>", "");
		process_failure(data, ERR_STAT);
	}
}

static void	eat_routine(t_philo *philo, t_data *data)
{
	handle_forks(philo, ST_TAKE, data);
	set_timer(&philo->mealtime,
		operate_timer(OP_MSEC, data) - data->epoch,
		&philo->mutex[MX_TIME], data);
	log_status(philo, ST_EAT);
	percision_sleep(data->input->time_to_eat, data);
	handle_forks(philo, ST_PUT, data);
	if (--philo->meals_to_eat == 0)
		set_status(&philo->stat[ST_FULL], true,
			&philo->mutex[MX_FULL], data);
}

void	*process_routine(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	threads_spinlocked(data);
	if (philo->id % 2 == 0)
	{
		log_status(philo, ST_THK);
		usleep(500);
	}
	while (true)
	{
		if (process_finished(data)
			|| process_failed(data))
			break ;
		eat_routine(philo, data);
		sleep_routine(philo, data);
	}
	return (NULL);
}
