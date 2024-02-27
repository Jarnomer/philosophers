/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:35:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/27 17:58:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->input->philos)
		operate_mutex(&data->forks[i], OP_DESTROY, data);
	i = MTX_NUM;
	while (--i >= 0)
		operate_mutex(&data->mutex[i], OP_DESTROY, data);
	if (data->stat[ST_ERR])
		return (FAILURE);
	return (SUCCESS);
}

static int	join_threads(t_data *data)
{
	t_philo	*phil;
	int		i;

	i = 0;
	while (i < data->input->philos)
	{
		phil = data->phils + i++;
		operate_thread(&phil->tid, OP_JOIN, data, NULL);
	}
	destroy_mutexes(data);
	free_mem(0, data, NULL);
	if (data->stat[ST_ERR])
		return (FAILURE);
	return (SUCCESS);
}

static int	init_threads(t_data *data)
{
	t_philo	*phil;
	int		i;

	i = 0;
	while (i < data->input->philos)
	{
		phil = data->phils + i++;
		operate_thread(&phil->tid, OP_CREATE, data, phil);
		if (data->stat[ST_ERR])
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < MTX_NUM)
	{
		operate_mutex(&data->mutex[i++], OP_INIT, data);
		if (data->stat[ST_ERR])
			return (FAILURE);
	}
	i = 0;
	while (i < data->input->philos)
	{
		operate_mutex(&data->forks[i++], OP_INIT, data);
		if (data->stat[ST_ERR])
			return (FAILURE);
	}
	return (SUCCESS);
}

int	process_manager(t_data *data)
{
	if (init_mutexes(data) != SUCCESS)
		return (destroy_mutexes(data));
	process_monitor(data);
	if (init_threads(data) != SUCCESS)
		return (join_threads(data));
	set_timer(&data->mutex[MX_TIME], &data->start,
		update_time(OP_MSEC, data), data);
	threads_synchronized(data);
	return (join_threads(data));
}
