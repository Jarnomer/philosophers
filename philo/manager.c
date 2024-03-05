/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:35:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/05 12:12:19 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexes(t_data *data)
{
	t_philo	*phil;
	int		i;
	int		j;

	i = 0;
	while (i < data->input->philos)
	{
		j = 0;
		phil = data->phils + i;
		while (j < MTX_NUM_P)
			operate_mutex(&phil->mutex[j++], OP_DESTROY, data);
		operate_mutex(&data->forks[i++], OP_DESTROY, data);
	}
	i = MTX_NUM_D;
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
	operate_thread(&data->tid, OP_DETACH, data, NULL);
	destroy_mutexes(data);
	free_mem(ST_DONE, data, NULL);
	if (data->stat[ST_ERR])
		return (FAILURE);
	return (SUCCESS);
}

static int	init_threads(t_data *data)
{
	t_philo	*phil;
	int		i;

	i = 0;
	while (i < data->input->philos && !data->stat[ST_ERR])
	{
		phil = data->phils + i++;
		operate_thread(&phil->tid, OP_CREATE, data, phil);
	}
	operate_thread(&data->tid, OP_CREATE, data, data);
	if (data->stat[ST_ERR])
		return (FAILURE);
	return (SUCCESS);
}

static int	init_mutexes(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MTX_NUM_D && !data->stat[ST_ERR])
		operate_mutex(&data->mutex[i++], OP_INIT, data);
	i = 0;
	while (i < data->input->philos && !data->stat[ST_ERR])
	{
		j = 0;
		while (j < MTX_NUM_P && !data->stat[ST_ERR])
			operate_mutex(&(data->phils + i)->mutex[j++], OP_INIT, data);
		operate_mutex(&data->forks[i++], OP_INIT, data);
	}
	if (data->stat[ST_ERR])
		return (FAILURE);
	return (SUCCESS);
}

int	process_manager(t_data *data)
{
	if (init_mutexes(data) != SUCCESS)
		return (destroy_mutexes(data));
	if (init_threads(data) != SUCCESS)
		return (join_threads(data));
	set_timer(&data->epoch, update_time(OP_MSEC, data),
		&data->mutex[MX_EPCH], data);
	threads_synchronized(data);
	return (join_threads(data));
}
