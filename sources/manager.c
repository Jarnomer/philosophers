/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:35:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/02 18:32:04 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	destroy_mutexes(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		j;

	i = 0;
	while (i < data->input->philo_count)
	{
		j = 0;
		philo = data->philos + i;
		while (j < MTX_COUNT_PHILO)
			operate_mutex(&philo->mutex[j++], OP_DESTROY, data);
		operate_mutex(&data->forks[i++], OP_DESTROY, data);
	}
	i = MTX_COUNT_DATA;
	while (--i >= 0)
		operate_mutex(&data->mutex[i], OP_DESTROY, data);
}

static void	join_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->input->philo_count)
	{
		philo = data->philos + i++;
		operate_thread(&philo->tid, OP_JOIN, data, NULL);
	}
	operate_thread(&data->monitor, OP_DETACH, data, NULL);
}

static void	init_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->input->philo_count && data->stat[ST_ERR] == false)
	{
		philo = data->philos + i++;
		operate_thread(&philo->tid, OP_CREATE, data, philo);
	}
	if (data->stat[ST_ERR] == false)
		operate_thread(&data->monitor, OP_CREATE, data, data);
}

static void	init_mutexes(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MTX_COUNT_DATA && data->stat[ST_ERR] == false)
		operate_mutex(&data->mutex[i++], OP_INIT, data);
	i = 0;
	while (i < data->input->philo_count && data->stat[ST_ERR] == false)
	{
		j = 0;
		while (j < MTX_COUNT_PHILO && data->stat[ST_ERR] == false)
			operate_mutex(&(data->philos + i)->mutex[j++], OP_INIT, data);
		if (data->stat[ST_ERR] == false)
			operate_mutex(&data->forks[i++], OP_INIT, data);
	}
}

int	process_manager(t_data *data)
{
	init_mutexes(data);
	init_threads(data);
	data->epoch = operate_timer(OP_MSEC, data);
	threads_synchronized(data);
	join_threads(data);
	destroy_mutexes(data);
	process_free(data);
	return (data->exitcode);
}
