/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:18:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/24 15:19:19 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_data *data, t_philo *phil, int i, int cnt)
{
	if (i != 0)
		phil->lf = data->forks + (i - 1);
	else
		phil->lf = data->forks + (cnt - 1);
	phil->rf = data->forks + i;
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
		phil->alive = true;
		phil->data = data;
		phil->id = i++;
	}
}

static int	fill_input(t_input *input, int ac, char **av)
{
	input->amount = custom_atol(av[1]);
	input->die = custom_atol(av[2]);
	input->eat = custom_atol(av[3]);
	input->sleep = custom_atol(av[4]);
	if (ac == 6)
		input->meals = custom_atol(av[5]);
	else
		input->meals = -1;
	return (input->amount);
}

int	init_data(t_data *data, int ac, char **av)
{
	int	cnt;

	memset(data, 0, sizeof(t_data));
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		return (free_out(FAILURE, NULL, MSG_MEM));
	cnt = fill_input(data->input, ac, av);
	data->phils = malloc(sizeof(t_philo) * cnt);
	data->forks = malloc(sizeof(t_fork) * cnt);
	if (!data->phils || !data->forks)
		return (free_out(FAILURE, data, MSG_MEM));
	init_philosophers(data, cnt);
	data->dine = &simulate_dinner;
	data->excode = SUCCESS;
	return (data->excode);
}
