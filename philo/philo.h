/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:38:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/24 15:19:01 by jmertane         ###   ########.fr       */
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
# define MSG_ARGC	"Number of argments must be 4 or 5\n"
# define MSG_EXAM	"./philo 5 1000 400 200 (10)\n"
# define MSG_HELP	"\
[5]:\t<number of philosophers>\n\
[1000]:\t<time to die>\n\
[400]:\t<time to eat>\n\
[200]:\t<time to sleep>\n\
[10]:\t<number of meals>\n"

# define BOLD_RED		"\033[1;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define PURPLE			"\033[0;35m"
# define RESET			"\033[0m"

typedef enum e_checker
{
	FAILURE = -1,
	SUCCESS = 0
}	t_checker;

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef enum e_operator
{
	CREATE,
	DETACH,
	JOIN,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_operator;

typedef struct s_fork
{
	int		id;
	t_mtx	mutex;
}	t_fork;

typedef struct s_input
{
	int	amount;
	int	die;
	int	eat;
	int	sleep;
	int	meals;
}	t_input;

typedef struct s_philo
{
	int			id;
	int			meals;
	bool		full;
	long		clock;
	bool		alive;
	pthread_t	tid;
	t_fork		*lf;
	t_fork		*rf;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	t_input		*input;
	t_philo		*phils;
	t_fork		*forks;
	int			excode;
	long		uptime;
	bool		finish;
	bool		synced;
	void		*(*dine)(void *);
}	t_data;

int		valid_arguments(int ac, char **av);
int		init_data(t_data *data, int ac, char **av);
int		start_simulation(t_data *data);
void	*simulate_dinner(void *param);
long	refresh_time(t_data *data);
int		operate_mutex(t_mtx *mutex, t_operator opr, t_data *data);
int		operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p);
int		error_logger(int errcode, char *s1, char *s2, char *s3);
int		print_usage(int errcode);
int		free_out(int errcode, t_data *data, char *msg);
long	custom_atol(const char *str);

#endif
