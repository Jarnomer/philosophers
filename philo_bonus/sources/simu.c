/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/31 10:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*run_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	long	current_time;

	philo = (t_philo *)arg;
	data = philo->data;
	while (true)
	{
		current_time = operate_timer(OP_MSEC, data);
		if (current_time - philo->last_meal > (long)data->input->time_to_die)
		{
			operate_semaphore(data->write, NULL, OP_WAIT, data);
			printf("%ld %d died\n", current_time - data->start_time, philo->id);
			operate_semaphore(data->death, NULL, OP_POST, data);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

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

static void	run_routine(t_philo *philo)
{
	t_data		*data;

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

int	run_simulation(t_data *data)
{
	int	i;
	int	meals_finished;

	i = 0;
	data->start_time = operate_timer(OP_MSEC, data);
	while (i < data->input->philo_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			error_exit(ERR_FORK, data, MSG_FORK);
		else if (data->pids[i] == 0)
			run_routine(&data->philos[i]);
		i++;
	}
	if (data->input->meals_count != -1)
	{
		meals_finished = 0;
		while (meals_finished < data->input->philo_count)
		{
			operate_semaphore(data->meals, NULL, OP_WAIT, data);
			meals_finished++;
		}
		operate_semaphore(data->death, NULL, OP_POST, data);
	}
	else
		operate_semaphore(data->death, NULL, OP_WAIT, data);
	return (0);
}
