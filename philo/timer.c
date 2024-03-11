/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:22:38 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/04 20:05:27 by jmertane         ###   ########.fr       */
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
		if (process_finished(data) || process_failed(data))
			break ;
		remain = target - gettime(start, data);
		if (remain > 1e3)
			usleep(remain / 2);
		else
			while (gettime(start, data) < target)
				true ;
	}
}

static char	*err_msg(int stat)
{
	if (stat == EFAULT)
		return ("Pointer outside accessible address space.");
	else if (stat == EINVAL)
		return ("Timezone or something else is invalid.");
	else if (stat == EPERM)
		return ("Calling process has insufficient privilege");
	return (NULL);
}

static void	wrapper(int stat, t_operator opr, t_data *data)
{
	if (stat != SUCCESS)
	{
		log_error(FAILURE, MSG_SYSC, "<gettimeofday>: ", err_msg(stat));
		error_occured(data, stat);
	}
	else if (opr != OP_MSEC && opr != OP_USEC)
	{
		log_error(FAILURE, MSG_OPER, "<gettimeofday>", "");
		error_occured(data, EXIT_FAILURE);
	}
}

t_ul	update_time(t_operator opr, t_data *data)
{
	struct timeval	tp;

	wrapper(gettimeofday(&tp, NULL), opr, data);
	if (process_failed(data))
		return (ULONG_MAX);
	else if (opr == OP_MSEC)
		return ((tp.tv_sec * 1e3) + (tp.tv_usec / 1e3));
	else
		return ((tp.tv_sec * 1e6) + tp.tv_usec);
}
