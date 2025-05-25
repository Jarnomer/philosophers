/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opsemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/01 10:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	*err_msg(int exitcode, t_operator opr)
{
	if (exitcode == EINVAL)
		return ("Invalid semaphore value.\n");
	else if (exitcode == EEXIST && opr == OP_OPEN)
		return ("Semaphore already exists.\n");
	else if (exitcode == ENOMEM)
		return ("Not enough memory.\n");
	else if (exitcode == ENOSPC)
		return ("Maximum value of semaphore would be exceeded.\n");
	else if (exitcode == EAGAIN && opr == OP_WAIT)
		return ("The semaphore could not be immediately locked.\n");
	else if (exitcode == EDEADLK && opr == OP_WAIT)
		return ("A deadlock was detected.\n");
	else
		return ("Unhandled semaphore error occurred.\n");
}

static char	*fn_name(t_operator opr)
{
	if (opr == OP_OPEN)
		return ("<sem_open>: ");
	else if (opr == OP_WAIT)
		return ("<sem_wait>: ");
	else if (opr == OP_POST)
		return ("<sem_post>: ");
	else if (opr == OP_CLOSE)
		return ("<sem_close>: ");
	else
		return ("<sem_unlink>: ");
}

static void	err_chk(int exitcode, t_operator opr, t_data *data)
{
	if (exitcode != 0)
	{
		log_error(ERR_SYSC, MSG_SYSC, fn_name(opr), err_msg(exitcode, opr));
		error_exit(exitcode, data, NULL);
	}
}

void	operate_semaphore(sem_t *sem, char *name, t_operator opr, t_data *data)
{
	if (opr == OP_WAIT)
		err_chk(sem_wait(sem), OP_WAIT, data);
	else if (opr == OP_POST)
		err_chk(sem_post(sem), OP_POST, data);
	else if (opr == OP_CLOSE)
		err_chk(sem_close(sem), OP_CLOSE, data);
	else if (opr == OP_UNLINK)
		err_chk(sem_unlink(name), OP_UNLINK, data);
	else
	{
		log_error(ERR_OPER, MSG_OPER, "<operate_semaphore> ", "");
		error_exit(ERR_OPER, data, NULL);
	}
}
