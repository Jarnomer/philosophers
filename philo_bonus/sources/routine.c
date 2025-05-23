/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/31 10:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	handle_forks(t_philo *philo, t_data *data)
{
	operate_semaphore(data->forks, NULL, OP_WAIT, data);
	log_status(philo, ST_TAKE);
	operate_semaphore(data->forks, NULL, OP_WAIT, data);
	log_status(philo, ST_TAKE);
}

static void	eat_routine(t_philo *philo, t_data *data)
{
	handle_forks(philo, data);
	philo->last_meal = operate_timer(OP_MSEC, data);
	log_status(philo, ST_EAT);
	precise_sleep(data->input->time_to_eat, data);
	philo->meals_eaten++;
	if (philo->meals_eaten >= data->input->meals_count
		&& data->input->meals_count != -1)
		operate_semaphore(data->meals, NULL, OP_POST, data);
	operate_semaphore(data->forks, NULL, OP_POST, data);
	operate_semaphore(data->forks, NULL, OP_POST, data);
}

void	run_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	philo->last_meal = operate_timer(OP_MSEC, data);
	operate_thread(&philo->tid, OP_CREATE, data, philo);
	if (philo->id % 2 == 0)
	{
		log_status(philo, ST_THK);
		usleep(500);
	}
	while (true)
	{
		eat_routine(philo, data);
		log_status(philo, ST_SLP);
		precise_sleep(data->input->time_to_sleep, data);
		log_status(philo, ST_THK);
	}
	operate_thread(&philo->tid, OP_DETACH, data, NULL);
	exit(EXIT_SUCCESS);
}
