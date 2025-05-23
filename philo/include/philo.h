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
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

# define MTX_COUNT_DATA 5
# define STT_COUNT_DATA 3
# define MTX_COUNT_PHILO 2
# define STT_COUNT_PHILO 2

typedef enum e_mutex
{
	MX_ERR		= 0,
	MX_SYNC,
	MX_DONE,
	MX_EPCH,
	MX_LOG,
	MX_FULL		= 0,
	MX_TIME,
}	t_mutex;

typedef enum e_state
{
	ST_ERR		= 0,
	ST_SYNC,
	ST_DONE,
	ST_FULL		= 0,
	ST_EAT,
	ST_TAKE,
	ST_PUT,
	ST_SLP,
	ST_THK,
	ST_DIE
}	t_state;

typedef enum e_operator
{
	OP_CREATE	= 0,
	OP_JOIN,
	OP_DETACH,
	OP_INIT		= 0,
	OP_LOCK,
	OP_UNLOCK,
	OP_DESTROY,
	OP_MSEC		= 0,
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
	long		mealtime;
	int			meals_to_eat;
	int			id;
	pthread_t	tid;
	t_mtx		*f1;
	t_mtx		*f2;
	t_mtx		mutex[MTX_COUNT_PHILO];
	bool		stat[STT_COUNT_PHILO];
}	t_philo;

typedef struct s_data
{
	t_input		*input;
	t_philo		*philos;
	t_mtx		*forks;
	long		epoch;
	long		uptime;
	int			exitcode;
	pthread_t	monitor;
	t_mtx		mutex[MTX_COUNT_DATA];
	bool		stat[STT_COUNT_DATA];
}	t_data;

int		valid_args(int argc, char **argv);
int		init_data(t_data *data, int argc, char **argv);

int		run_simulation(t_data *data);
void	*run_monitor(void *param);
void	*run_routine(void *param);

void	operate_mutex(t_mtx *mutex, t_operator opr, t_data *data);
void	operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p);
long	operate_timer(t_operator opr, t_data *data);

void	log_status(t_philo *philo, t_state state);
int		log_error(int errcode, char *s1, char *s2, char *s3);

void	precise_sleep(long goal, t_data *data);
int		error_exit(int errcode, t_data *data, char *msg);
void	process_free(t_data *data);
int		print_usage(int errcode);
long	ft_atol(const char *str);

void	set_finished(t_data *data);
void	set_status(bool *dst, bool val, t_mtx *mutex, t_data *data);
bool	get_status(bool *val, t_mtx *mutex, t_data *data);
void	set_timer(long *dst, long val, t_mtx *mutex, t_data *data);
long	get_timer(long *val, t_mtx *mutex, t_data *data);

void	threads_synchronized(t_data *data);
void	threads_spinlocked(t_data *data);
bool	process_finished(t_data *data);
bool	process_failed(t_data *data);
void	process_failure(t_data *data, int errcode);

#endif
