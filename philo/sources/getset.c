/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:20 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/28 16:39:01 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_finished(t_data *data)
{
	set_status(&data->stat[ST_DONE], true, &data->mutex[MX_DONE], data);
}

void	set_status(bool *dst, bool val, t_mtx *mutex, t_data *data)
{
	operate_mutex(mutex, OP_LOCK, data);
	*dst = val;
	operate_mutex(mutex, OP_UNLOCK, data);
}

bool	get_status(bool *val, t_mtx *mutex, t_data *data)
{
	bool	ret;

	operate_mutex(mutex, OP_LOCK, data);
	ret = *val;
	operate_mutex(mutex, OP_UNLOCK, data);
	return (ret);
}

void	set_timer(long *dst, long val, t_mtx *mutex, t_data *data)
{
	operate_mutex(mutex, OP_LOCK, data);
	*dst = val;
	operate_mutex(mutex, OP_UNLOCK, data);
}

long	get_timer(long *val, t_mtx *mutex, t_data *data)
{
	long	ret;

	operate_mutex(mutex, OP_LOCK, data);
	ret = *val;
	operate_mutex(mutex, OP_UNLOCK, data);
	return (ret);
}
