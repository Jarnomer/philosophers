/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:50:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/21 11:50:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	cleanup_semaphores(t_data *data)
{
	operate_semaphore(data->forks, NULL, OP_CLOSE, data);
	operate_semaphore(data->write, NULL, OP_CLOSE, data);
	operate_semaphore(data->death, NULL, OP_CLOSE, data);
	operate_semaphore(data->meals, NULL, OP_CLOSE, data);
	operate_semaphore(NULL, SEM_FORKS, OP_UNLINK, data);
	operate_semaphore(NULL, SEM_WRITE, OP_UNLINK, data);
	operate_semaphore(NULL, SEM_DEATH, OP_UNLINK, data);
	operate_semaphore(NULL, SEM_MEALS, OP_UNLINK, data);
}

static void	wait_children(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->input->philo_count)
	{
		waitpid(data->pids[i], &status, 0);
		i++;
	}
}

static void	kill_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input->philo_count)
	{
		kill(data->pids[i], SIGTERM);
		i++;
	}
}

void	process_free(t_data *data)
{
	if (!data)
		return ;
	kill_philosophers(data);
	wait_children(data);
	cleanup_semaphores(data);
	free(data->input);
	free(data->philos);
	free(data->pids);
}
