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

static void	destroy_mutexes(t_data *data)
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
}

static void	join_threads(t_data *data)
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
}

static void	init_threads(t_data *data)
{
	t_philo	*phil;
	int		i;

	i = 0;
	while (i < data->input->philos && !data->stat[ST_ERR])
	{
		phil = data->phils + i++;
		operate_thread(&phil->tid, OP_CREATE, data, phil);
	}
	if (!data->stat[ST_ERR])
		operate_thread(&data->tid, OP_CREATE, data, data);
}

static void	init_mutexes(t_data *data)
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
}

int	process_manager(t_data *data)
{
	init_mutexes(data);
	init_threads(data);
	printf("-----------------------------------------\n");
	printf("|%s  SIMULATION START %s\t\t\t|\n", RB, T);
	printf("-----------------------------------------\n");
	data->epoch = update_time(OP_MSEC, data);
	threads_synchronized(data);
	join_threads(data);
	destroy_mutexes(data);
	free_mem(0, data, NULL);
	printf("-----------------------------------------\n");
	printf("|%s  SIMULATION END %s\t\t\t|\n", RB, T);
	printf("-----------------------------------------\n");
	return (data->excode);
}
