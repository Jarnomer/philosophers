/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:18:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/25 18:42:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_data *data, t_philo *phil, int i, int cnt)
{
	int	j;

	j = (i + 1) % cnt;
	if (i % 2 == 0)
	{
		phil->f1 = data->forks + i;
		phil->f2 = data->forks + j;
	}
	else
	{
		phil->f2 = data->forks + i;
		phil->f1 = data->forks + j;
	}
}

static void	init_philosophers(t_data *data, int cnt)
{
	t_philo	*phil;
	int		i;

	i = 0;
	while (i < cnt)
	{
		phil = data->phils + i;
		memset(phil, 0, sizeof(t_philo));
		assign_forks(data, phil, i, cnt);
		phil->meals = data->input->meals;
		phil->data = data;
		phil->id = 1 + i++;
	}
}

static int	fill_input(t_input *input, int ac, char **av)
{
	input->philos = custom_atol(av[1]);
	input->die = custom_atol(av[2]);
	input->eat = custom_atol(av[3]);
	input->sleep = custom_atol(av[4]);
	if (ac == 6)
		input->meals = custom_atol(av[5]);
	else
		input->meals = -1;
	return (input->philos);
}

int	init_data(t_data *data, int ac, char **av)
{
	int	cnt;

	memset(data, 0, sizeof(t_data));
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		return (free_mem(ENOMEM, NULL, MSG_MEM));
	cnt = fill_input(data->input, ac, av);
	data->phils = malloc(sizeof(t_philo) * cnt);
	data->forks = malloc(sizeof(t_mtx) * cnt);
	if (!data->phils || !data->forks)
		return (free_mem(ENOMEM, data, MSG_MEM));
	init_philosophers(data, cnt);
	data->fn = &process_monitor;
	return (SUCCESS);
}
