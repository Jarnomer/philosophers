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
			log_status(philo, ST_DIE);
			operate_semaphore(data->death, NULL, OP_POST, data);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

static void	start_philosophers(t_data *data)
{
	int	i;

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
}

int	run_simulation(t_data *data)
{
	int	meals_finished;

	start_philosophers(data);
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
