/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:49:40 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/23 16:49:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexes(t_data *data, int cnt)
{
	t_fork	*fork;
	int		status;
	int		i;

	i = 0;
	while (i <= cnt)
	{
		fork = data->forks + i;
		status = operate_mutex(&fork->mutex, DESTROY, data);
		if (status != SUCCESS)
			data->excode = status;
		i++;
	}
	if (data->excode != SUCCESS)
		return (free_out(FAILURE, data, NULL));
	return (SUCCESS);
}

static int	join_threads(t_data *data, int cnt)
{
	t_philo	*phil;
	int		status;
	int		i;

	i = 0;
	while (i <= cnt)
	{
		phil = data->phils + i;
		status = operate_thread(&phil->tid, JOIN, data, phil);
		if (status != SUCCESS)
			data->excode = status;
		i++;
	}
	if (data->excode != SUCCESS)
	{
		destroy_mutexes(data, data->input->amount);
		return (free_out(FAILURE, data, NULL));
	}
	return (SUCCESS);
}

static int	init_threads(t_data *data, int i)
{
	t_philo	*phil;

	phil = data->phils + i;
	data->excode = operate_thread(&phil->tid, CREATE, data, phil);
	if (data->excode != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int	init_mutexes(t_data *data, int i)
{
	t_fork	*fork;

	fork = data->forks + i;
	data->excode = operate_mutex(&fork->mutex, INIT, data);
	if (data->excode != SUCCESS)
		return (FAILURE);
	fork->id = i;
	return (SUCCESS);
}

int	start_simulation(t_data *data)
{
	int	cnt;
	int	i;

	i = -1;
	cnt = data->input->amount;
	while (++i < cnt)
		if (init_mutexes(data, i) != SUCCESS)
			return (destroy_mutexes(data, --i));
	i = -1;
	while (++i < cnt)
		if (init_threads(data, i) != SUCCESS)
			return (join_threads(data, --i));
	if (join_threads(data, cnt - 1) == SUCCESS)
		destroy_mutexes(data, cnt -1);
	return (free_out(SUCCESS, data, NULL));
}
