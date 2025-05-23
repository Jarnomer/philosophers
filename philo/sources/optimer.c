/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:22:38 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/30 19:38:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	*err_msg(int exitcode)
{
	if (exitcode == EFAULT)
		return ("Pointer outside accessible address space.\n");
	else if (exitcode == EINVAL)
		return ("Timezone or something else is invalid.\n");
	else if (exitcode == EPERM)
		return ("Calling process has insufficient privilege.\n");
	else
		return ("Unhandled <operate_timer> error occured.\n");
}

static void	err_chk(int exitcode, t_data *data)
{
	if (exitcode != 0)
	{
		log_error(ERR_SYSC, MSG_SYSC, "<gettimeofday>: ", err_msg(exitcode));
		process_failure(data, exitcode);
	}
}

long	operate_timer(t_operator opr, t_data *data)
{
	struct timeval	tp;

	err_chk(gettimeofday(&tp, NULL), data);
	if (opr == OP_MSEC)
		return ((tp.tv_sec * 1e3) + (tp.tv_usec / 1e3));
	else if (opr == OP_USEC)
		return ((tp.tv_sec * 1e6) + tp.tv_usec);
	else
	{
		log_error(ERR_OPER, MSG_OPER, "<gettimeofday>: ", "");
		process_failure(data, ERR_OPER);
		return (0);
	}
}
