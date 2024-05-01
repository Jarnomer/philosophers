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

#include "philo.h"

static inline t_ul	gettime(t_ul start, t_data *data)
{
	return (update_time(OP_USEC, data) - start);
}

void	percision_sleep(t_ul target, t_data *data)
{
	long	start;

	target *= 1000;
	start = update_time(OP_USEC, data);
	while (gettime(start, data) < target)
	{
		if (process_finished(data) || process_failed(data))
			break ;
		usleep(500);
	}
}

static char	*err_msg(int stat)
{
	if (stat == EFAULT)
		return ("Pointer outside accessible address space.\n");
	else if (stat == EINVAL)
		return ("Timezone or something else is invalid.\n");
	else if (stat == EPERM)
		return ("Calling process has insufficient privilege.\n");
	else
		return ("Unhandled <update_time> error occured.\n");
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
	if (opr == OP_MSEC)
		return ((tp.tv_sec * 1e3) + (tp.tv_usec / 1e3));
	else if (opr == OP_USEC)
		return ((tp.tv_sec * 1e6) + tp.tv_usec);
	else
		return (EXIT_FAILURE);
}
