/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:38:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/26 08:13:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_ARGV	"Is invalid argument"
# define MSG_MEM	"Out of memory"
# define MSG_SYSC	"System call error in "
# define MSG_OPER	"Invalid operator in "
# define MSG_CNT	"Number of philosopher or meals can't be 0"
# define MSG_ARGC	"Number of argments must be 4 or 5\n"
# define MSG_EXAM	"./philo 5 1000 400 200 (10)\n"
# define MSG_HELP	"\
[5]:\t<number of philosophers>\n\
[1000]:\t<time to die>\n\
[400]:\t<time to eat>\n\
[200]:\t<time to sleep>\n\
[10]:\t<number of meals>\n"

# define RB		"\033[1;31m"
# define CB		"\033[1;36m"
# define G		"\033[0;32m"
# define Y		"\033[0;33m"
# define P		"\033[0;35m"
# define T		"\033[0m"

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;
typedef unsigned long	t_ul;

# define MTX_NUM	5
# define STAT_NUM	3
# define ST_PH_N	3

typedef enum e_check
{
	FAILURE = -1,
	SUCCESS = 0,
}	t_check;

typedef enum e_mutex
{
	MX_ERR,
	MX_SYNC,
	MX_TIME,
	MX_DONE,
	MX_LOG
}	t_mutex;

typedef enum e_status
{
	ST_ERR,
	ST_SYNC,
	ST_DONE
}	t_status;

typedef enum e_state
{
	ST_EATING,
	ST_FULL,
	ST_DEATH,
	ST_TAKE,
	ST_SLEEP,
	ST_THINK,
}	t_state;

typedef enum e_operator
{
	OP_CREATE,
	OP_DETACH,
	OP_JOIN,
	OP_INIT,
	OP_LOCK,
	OP_UNLOCK,
	OP_DESTROY,
	OP_MSEC,
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
	int			id;
	int			meals;
	bool		*stat[ST_PH_N];
	t_ul		timer;
	pthread_t	tid;
	t_mtx		*f1;
	t_mtx		*f2;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	t_input		*input;
	t_philo		*phils;
	t_mtx		*forks;
	t_mtx		mutex[MTX_NUM];
	bool		stat[STAT_NUM];
	void		*(*fn)(void *);
	t_ul		start;
}	t_data;

int		valid_args(int ac, char **av);
long	custom_atol(const char *str);
int		init_data(t_data *data, int ac, char **av);
int		process_manager(t_data *data);
void	*process_monitor(void *param);
void	operate_mutex(t_mtx *mutex, t_operator opr, t_data *data);
void	operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p);
int		log_usage(int errcode);
void	log_status(t_philo *phil, t_state flg);
int		log_error(int errcode, char *s1, char *s2, char *s3);
void	mutate_status(t_mtx *mutex, bool *dst, bool val, t_data *data);
bool	access_status(t_mtx *mutex, bool *val, t_data *data);
void	mutate_timer(t_mtx *mutex, t_ul *dst, t_ul val, t_data *data);
t_ul	access_timer(t_mtx *mutex, t_ul *val, t_data *data);
t_ul	update_timer(t_operator opr, t_data *data);
void	percision_sleep(long goal, t_data *data);
int		free_mem(int errcode, t_data *data, char *msg);
void	synchronize_threads(t_data *data);
void	spinlock_threads(t_data *data);
bool	process_finished(t_data *data);
bool	process_error(t_data *data);
void	error_occured(t_data *data);

#endif
