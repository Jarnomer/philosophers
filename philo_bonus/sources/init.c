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

static inline sem_t	*open_semaphore(const char *name, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0644, value);
	return (sem);
}

static int	init_semaphores(t_data *data)
{
	int	count;

	count = data->input->philo_count;
	data->forks = open_semaphore(SEM_FORKS, count);
	data->write = open_semaphore(SEM_WRITE, 1);
	data->death = open_semaphore(SEM_DEATH, 0);
	data->meals = open_semaphore(SEM_MEALS, 0);
	if (data->forks == SEM_FAILED || data->write == SEM_FAILED
		|| data->death == SEM_FAILED || data->meals == SEM_FAILED)
		return (-1);
	return (0);
}

static void	init_philosophers(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->input->philo_count)
	{
		philo = data->philos + i;
		memset(philo, 0, sizeof(t_philo));
		philo->data = data;
		philo->id = 1 + i++;
	}
}

static int	fill_input(t_input *input, int argc, char **argv)
{
	input->philo_count = ft_atol(argv[1]);
	input->time_to_die = ft_atol(argv[2]);
	input->time_to_eat = ft_atol(argv[3]);
	input->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		input->meals_count = ft_atol(argv[5]);
	else
		input->meals_count = -1;
	return (input->philo_count);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	philo_count;

	memset(data, 0, sizeof(t_data));
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		error_exit(ERR_MEM, NULL, MSG_MEM);
	philo_count = fill_input(data->input, argc, argv);
	data->philos = malloc(sizeof(t_philo) * philo_count);
	data->pids = malloc(sizeof(pid_t) * philo_count);
	if (!data->philos || !data->pids)
		error_exit(ERR_MEM, data, MSG_MEM);
	init_philosophers(data);
	if (init_semaphores(data) == -1)
		error_exit(ERR_SEM, data, MSG_SEM);
	return (data->exitcode);
}
