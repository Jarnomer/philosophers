/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opthread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:03:58 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/30 19:34:18 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	*err_msg(int exitcode, t_operator opr)
{
	if (exitcode == ESRCH && (opr == OP_DETACH || opr == OP_JOIN))
		return ("No thread with ID could be found.\n");
	else if (exitcode == EINVAL && (opr == OP_DETACH || opr == OP_JOIN))
		return ("Thread is not a joinable thread.\n");
	else if (exitcode == EDEADLK && opr == OP_JOIN)
		return ("Deadlock was detected.\n");
	else if (exitcode == EAGAIN && opr == OP_CREATE)
		return ("Insufficient resources to create another thread.\n");
	else
		return ("Unhandled <operate_thread> error occured.\n");
}

static char	*fn_name(t_operator opr)
{
	if (opr == OP_CREATE)
		return ("<pthread_create>: ");
	else if (opr == OP_DETACH)
		return ("<pthread_detach>: ");
	else
		return ("<pthread_join>: ");
}

static void	err_chk(int exitcode, t_operator opr, t_data *data)
{
	if (exitcode != 0)
	{
		log_error(ERR_SYSC, MSG_SYSC, fn_name(opr), err_msg(exitcode, opr));
		error_exit(exitcode, data, NULL);
	}
}

void	operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p)
{
	if (opr == OP_CREATE)
		err_chk(pthread_create(tid, NULL, run_monitor, p), opr, data);
	else if (opr == OP_JOIN)
		err_chk(pthread_join(*tid, NULL), opr, data);
	else if (opr == OP_DETACH)
		err_chk(pthread_detach(*tid), opr, data);
	else
	{
		log_error(ERR_OPER, MSG_OPER, "<operate_thread>", "");
		error_exit(ERR_OPER, data, NULL);
	}
}
