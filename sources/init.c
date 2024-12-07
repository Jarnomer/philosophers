/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:18:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/01 14:51:30 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	assign_forks(t_data *data, t_philo *philo, int i, int philo_count)
{
	int	j;

	j = (i + 1) % philo_count;
	if (i % 2 == 0)
	{
		philo->f1 = data->forks + i;
		philo->f2 = data->forks + j;
	}
	else
	{
		philo->f2 = data->forks + i;
		philo->f1 = data->forks + j;
	}
}

static void	init_philosophers(t_data *data, int philo_count)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < philo_count)
	{
		philo = data->philos + i;
		memset(philo, 0, sizeof(t_philo));
		assign_forks(data, philo, i, philo_count);
		philo->meals_to_eat = data->input->meals_count;
		philo->data = data;
		philo->id = 1 + i++;
	}
}

static int	fill_input(t_input *input, int argc, char **argv)
{
	input->philo_count = custom_atol(argv[1]);
	input->time_to_die = custom_atol(argv[2]);
	input->time_to_eat = custom_atol(argv[3]);
	input->time_to_sleep = custom_atol(argv[4]);
	if (argc == 6)
		input->meals_count = custom_atol(argv[5]);
	else
		input->meals_count = -1;
	return (input->philo_count);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int		philo_count;

	memset(data, 0, sizeof(t_data));
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		return (error_exit(ERR_MEM, NULL, MSG_MEM));
	philo_count = fill_input(data->input, argc, argv);
	data->philos = malloc(sizeof(t_philo) * philo_count);
	data->forks = malloc(sizeof(t_mtx) * philo_count);
	if (!data->philos || !data->forks)
		return (error_exit(ERR_MEM, data, MSG_MEM));
	init_philosophers(data, philo_count);
	data->exitcode = 0;
	return (0);
}
