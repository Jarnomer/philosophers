/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opmutex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:54:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/04 18:35:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*err_msg(int stat, t_operator opr)
{
	if (stat == EINVAL && (opr == OP_LOCK || opr == OP_UNLOCK))
		return ("Mutex has not been properly initialized.\n");
	else if (stat == EDEADLK && opr == OP_LOCK)
		return ("Mutex is already locked by calling thread.\n");
	else if (stat == EPERM && opr == OP_UNLOCK)
		return ("Calling thread does not own the mutex.\n");
	else if (stat == EBUSY && opr == OP_DESTROY)
		return ("Mutex is currently locked.\n");
	else
		return ("Unhandled mutex error\n");
}

static char	*fn_name(t_operator opr)
{
	if (opr == OP_LOCK)
		return ("<pthread_mutex_lock>: ");
	else if (opr == OP_UNLOCK)
		return ("<pthread_mutex_unlock>: ");
	else if (opr == OP_INIT)
		return ("<pthread_mutex_init>: ");
	else
		return ("<pthread_mutex_destroy>: ");
}

static void	wrapper(int stat, t_operator opr, t_data *data)
{
	if (stat != SUCCESS)
	{
		log_error(FAILURE, MSG_SYSC, fn_name(opr), err_msg(stat, opr));
		error_occured(data, stat);
	}
}

void	operate_mutex(t_mtx *mutex, t_operator opr, t_data *data)
{
	if (opr == OP_INIT)
		wrapper(pthread_mutex_init(mutex, NULL), opr, data);
	else if (opr == OP_LOCK)
		wrapper(pthread_mutex_lock(mutex), opr, data);
	else if (opr == OP_UNLOCK)
		wrapper(pthread_mutex_unlock(mutex), opr, data);
	else if (opr == OP_DESTROY)
		wrapper(pthread_mutex_destroy(mutex), opr, data);
	else
	{
		log_error(FAILURE, MSG_OPER, "<operate_mutex>", "");
		error_occured(data, EXIT_FAILURE);
	}
}
