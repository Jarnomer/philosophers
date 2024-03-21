/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:38:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/13 11:19:03 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define MSG_ARGV "Is invalid argument, enter value between 1 - INT_MAX"
# define MSG_MEM "Out of memory"
# define MSG_SYSC "System call error in "
# define MSG_OPER "Invalid operator in "
# define MSG_STAT "Invalid state in "
# define MSG_ARGC "Number of argments must be 4 or 5\n"
# define MSG_EXAM "./philo 2 600 300 200 (4)\n"
# define MSG_HELP "\
[2]:\t<number of philosophers>\n\
[600]:\t<time to die>\n\
[300]:\t<time to eat>\n\
[200]:\t<time to sleep>\n\
[4]:\t<number of meals>\n"

# define RB "\033[1;31m"
# define CB "\033[1;36m"
# define BB "\033[1;34m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define P "\033[0;35m"
# define T "\033[0m"

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;
typedef unsigned long	t_ul;

# define MTX_NUM_D 6
# define STT_NUM_D 3
# define MTX_NUM_P 2
# define STT_NUM_P 2

typedef enum e_check
{
	FAILURE =	-1,
	SUCCESS =	0,
}	t_check;

typedef enum e_mutex
{
	MX_ERR		= 0,
	MX_SYNC,
	MX_DONE,
	MX_ITER,
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
	ST_LEAD		= 0,
	ST_FULL,
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
	int			philos;
	int			die;
	int			eat;
	int			sleep;
	int			meals;
}	t_input;

typedef struct s_philo
{
	t_data		*data;
	t_ul		cooldown;
	t_ul		mealtime;
	int			meals;
	int			id;
	pthread_t	tid;
	t_mtx		*f1;
	t_mtx		*f2;
	t_mtx		mutex[MTX_NUM_P];
	bool		stat[STT_NUM_P];
}	t_philo;

typedef struct s_data
{
	t_input		*input;
	t_philo		*phils;
	t_mtx		*forks;
	t_ul		epoch;
	t_ul		uptime;
	int			excode;
	pthread_t	tid;
	t_mtx		mutex[MTX_NUM_D];
	bool		stat[STT_NUM_D];
}	t_data;

int		valid_args(int ac, char **av);
long	custom_atol(const char *str);
int		init_data(t_data *data, int ac, char **av);
int		process_manager(t_data *data);
void	*process_monitor(void *param);
void	*process_routine(void *param);
void	*process_loner(void *param);
void	operate_mutex(t_mtx *mutex, t_operator opr, t_data *data);
void	operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p);
void	log_status(t_philo *phil, t_state state);
int		log_error(int errcode, char *s1, char *s2, char *s3);
void	set_status(bool *dst, bool val, t_mtx *mutex, t_data *data);
bool	get_status(bool *val, t_mtx *mutex, t_data *data);
void	set_timer(t_ul *dst, t_ul val, t_mtx *mutex, t_data *data);
t_ul	get_timer(t_ul *val, t_mtx *mutex, t_data *data);
void	alter_iterator(int *i, t_mtx *mutex, t_data *data);
t_ul	update_time(t_operator opr, t_data *data);
void	percision_sleep(t_ul goal, t_data *data);
void	threads_synchronized(t_data *data);
void	threads_spinlocked(t_data *data);
bool	process_finished(t_data *data);
bool	process_failed(t_data *data);
void	error_occured(t_data *data, int errcode);
int		print_usage(int errcode);
int		free_mem(int errcode, t_data *data, char *msg);

#endif
