/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:38:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/28 19:12:27 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <error.h>

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_data	t_data;

# define SEM_FORKS "/philo_forks"
# define SEM_WRITE "/philo_write"
# define SEM_DEATH "/philo_death"
# define SEM_MEALS "/philo_meals"

typedef enum e_state
{
	ST_TAKE,
	ST_EAT,
	ST_SLP,
	ST_THK,
	ST_DIE
}	t_state;

typedef enum e_operator
{
	OP_CREATE,
	OP_JOIN,
	OP_DETACH,
	OP_OPEN,
	OP_WAIT,
	OP_POST,
	OP_CLOSE,
	OP_UNLINK,
	OP_MSEC,
	OP_USEC
}	t_operator;

typedef struct s_input
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_count;
}	t_input;

typedef struct s_philo
{
	t_data		*data;
	long		last_meal;
	int			meals_eaten;
	int			id;
	pthread_t	tid;
	pid_t		pid;
}	t_philo;

typedef struct s_data
{
	t_input		*input;
	t_philo		*philos;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*write;
	sem_t		*death;
	sem_t		*meals;
	long		start_time;
	int			exitcode;
}	t_data;

int		init_data(t_data *data, int argc, char **argv);

int		run_simulation(t_data *data);
void	*run_monitor(void *arg);

void	operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p);
void	operate_semaphore(sem_t *sem, char *name, t_operator opr, t_data *data);
long	operate_timer(t_operator opr, t_data *data);

void	precise_sleep(int target_time, t_data *data);

int		log_error(int errcode, char *s1, char *s2, char *s3);
void	log_status(t_philo *philo, t_state state);

void	error_exit(int errcode, t_data *data, char *msg);
void	process_free(t_data *data);

int		valid_args(int argc, char **argv);
long	ft_atol(const char *str);
int		print_usage(int errcode);

#endif
