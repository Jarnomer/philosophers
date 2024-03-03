/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opthread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:03:58 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/29 08:22:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*err_msg(int stat, t_operator opr)
{
	if (stat == ESRCH && (opr == OP_DETACH || opr == OP_JOIN))
		return ("No thread with ID could be found.\n");
	else if (stat == EINVAL && (opr == OP_DETACH || opr == OP_JOIN))
		return ("Thread is not a joinable thread.\n");
	else if (stat == EDEADLK && opr == OP_JOIN)
		return ("Deadlock was detected.\n");
	else if (stat == EAGAIN && opr == OP_CREATE)
		return ("Insufficient resources to create another thread.\n");
	return (NULL);
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

static void	handler(int stat, t_operator opr, t_data *data)
{
	if (stat != SUCCESS)
	{
		log_error(FAILURE, MSG_SYSC, fn_name(opr), err_msg(stat, opr));
		error_occured(data, stat);
	}
}

void	operate_thread(pthread_t *tid, t_operator opr, t_data *data, void *p)
{
	static int	i = 0;

	if (opr == OP_CREATE)
	{
		if (i < data->input->philos)
			handler(pthread_create(tid, NULL, data->fn, p), opr, data);
		else
			handler(pthread_create(tid, NULL, data->mn, p), opr, data);
		alter_iterator(&data->mutex[MX_ITER], &i, true, data);
	}
	else if (opr == OP_JOIN)
		handler(pthread_join(*tid, NULL), opr, data);
	else if (opr == OP_DETACH)
		handler(pthread_detach(*tid), opr, data);
	else
	{
		log_error(FAILURE, MSG_OPER, "<operate_thread>", "");
		error_occured(data, EXIT_FAILURE);
	}
}
