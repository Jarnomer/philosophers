/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opmutex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:54:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/30 19:34:23 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	*err_msg(int exitcode, t_operator opr)
{
	if (exitcode == EINVAL && (opr == OP_LOCK || opr == OP_UNLOCK))
		return ("Mutex has not been properly initialized.\n");
	else if (exitcode == EDEADLK && opr == OP_LOCK)
		return ("Mutex is already locked by calling thread.\n");
	else if (exitcode == EPERM && opr == OP_UNLOCK)
		return ("Calling thread does not own the mutex.\n");
	else if (exitcode == EBUSY && opr == OP_DESTROY)
		return ("Mutex is currently locked.\n");
	else
		return ("Unhandled <operate_mutex> error occured.\n");
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

static void	err_chk(int exitcode, t_operator opr, t_data *data)
{
	if (exitcode != 0)
	{
		log_error(ERR_SYSC, MSG_SYSC, fn_name(opr), err_msg(exitcode, opr));
		process_failure(data, exitcode);
	}
}

void	operate_mutex(t_mtx *mutex, t_operator opr, t_data *data)
{
	if (opr == OP_INIT)
		err_chk(pthread_mutex_init(mutex, NULL), opr, data);
	else if (opr == OP_LOCK)
		err_chk(pthread_mutex_lock(mutex), opr, data);
	else if (opr == OP_UNLOCK)
		err_chk(pthread_mutex_unlock(mutex), opr, data);
	else if (opr == OP_DESTROY)
		err_chk(pthread_mutex_destroy(mutex), opr, data);
	else
	{
		log_error(ERR_OPER, MSG_OPER, "<operate_mutex> ", "");
		process_failure(data, ERR_OPER);
	}
}
