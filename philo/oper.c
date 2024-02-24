/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:54:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/23 06:25:39 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_thread_error(t_operator opr, int excode)
{
	if (excode == ESRCH && (opr == DETACH || opr == JOIN))
		return ("No thread with the ID could be found.");
	else if (excode == EINVAL && (opr == DETACH || opr == JOIN))
		return ("Thread is not a joinable thread.");
	else if (excode == EINVAL && opr == CREATE)
		return ("Invalid settings in attr.");
	else if (excode == EPERM && opr == CREATE)
		return ("No permission to set policy and parameters in attr.");
	else if (excode == EAGAIN && opr == CREATE)
		return ("Insufficient resources to create another thread.");
	else
		return ("A deadlock was detected.");
}

static char	*get_mutex_error(t_operator opr, int excode)
{
	if (excode == EINVAL && (opr == LOCK || opr == UNLOCK))
		return ("The mutex has not been properly initialized.");
	else if (excode == EDEADLK && opr == LOCK)
		return ("The mutex is already locked by the calling thread.");
	else if (excode == EPERM && opr == UNLOCK)
		return ("The calling thread does not own the mutex.");
	else
		return ("The mutex is currently locked.");
}

static char	*get_syscall_name(t_operator opr)
{
	if (opr == CREATE)
		return ("<pthread_create>: ");
	else if (opr == DETACH)
		return ("<pthread_detach>: ");
	else if (opr == JOIN)
		return ("<pthread_join>: ");
	else if (opr == INIT)
		return ("<pthread_mutex_init>: ");
	else if (opr == LOCK)
		return ("<pthread_mutex_lock>: ");
	else if (opr == UNLOCK)
		return ("<pthread_mutex_unlock>: ");
	else
		return ("<pthread_mutex_destroy>: ");
}

int	operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p)
{
	if (opr == CREATE)
		data->excode = pthread_create(tid, NULL, data->dine, p);
	else if (opr == DETACH)
		data->excode = pthread_detach(*tid);
	else if (opr == JOIN)
		data->excode = pthread_join(*tid, NULL);
	if (data->excode != SUCCESS)
		return (error_logger(FAILURE,
				MSG_SYSC, get_syscall_name(opr),
				get_thread_error(opr, data->excode)));
	return (SUCCESS);
}

int	operate_mutex(t_mtx *mutex, t_operator opr, t_data *data)
{
	if (opr == INIT)
		data->excode = pthread_mutex_init(mutex, NULL);
	else if (opr == LOCK)
		data->excode = pthread_mutex_lock(mutex);
	else if (opr == UNLOCK)
		data->excode = pthread_mutex_unlock(mutex);
	else if (opr == DESTROY)
		data->excode = pthread_mutex_destroy(mutex);
	if (data->excode != SUCCESS)
		return (error_logger(FAILURE,
				MSG_SYSC, get_syscall_name(opr),
				get_mutex_error(opr, data->excode)));
	return (SUCCESS);
}
