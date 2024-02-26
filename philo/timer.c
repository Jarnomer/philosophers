/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:22:38 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/26 19:19:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline t_ul	gettime(t_ul start, t_data *data)
{
	return (update_time(OP_USEC, data) - start);
}

void	percision_sleep(t_ul target, t_data *data)
{
	long	start;
	long	remain;

	target *= 1e3;
	start = update_time(OP_USEC, data);
	while (gettime(start, data) < target)
	{
		if (process_finished(data)
			|| process_error(data))
			break ;
		remain = target - gettime(start, data);
		if (remain > 1500)
			usleep(remain / 2);
		else
			while (gettime(start, data) < target)
				true ;
	}
}

static char	*errno_msg(int stat)
{
	if (stat == EFAULT)
		return ("Pointer outside accessible address space.");
	else if (stat == EINVAL)
		return ("Timezone or something else is invalid.");
	else if (stat == EPERM)
		return ("Calling process has insufficient privilege");
	return (NULL);
}

static void	handler(int stat, t_operator opr, t_data *data)
{
	char	*msg;

	msg = errno_msg(stat);
	if (msg != NULL)
	{
		log_error(FAILURE, MSG_SYSC, "<gettimeofday>: ", msg);
		error_occured(data);
	}
	else if (opr != OP_MSEC && opr != OP_USEC)
	{
		log_error(FAILURE, MSG_OPER, "<gettimeofday>", "");
		error_occured(data);
	}
}

t_ul	update_time(t_operator opr, t_data *data)
{
	struct timeval	tp;

	handler(gettimeofday(&tp, NULL), opr, data);
	if (process_finished(data) || process_error(data))
		return (ULONG_MAX);
	else if (opr == OP_MSEC)
		return ((tp.tv_sec * 1e3) + (tp.tv_usec / 1e3));
	else
		return ((tp.tv_sec * 1e6) + tp.tv_usec);
}
