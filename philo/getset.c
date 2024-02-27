/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:20 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/27 16:54:06 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_status(t_mtx *mutex, bool *dst, bool val, t_data *data)
{
	operate_mutex(mutex, OP_LOCK, data);
	*dst = val;
	operate_mutex(mutex, OP_UNLOCK, data);
}

bool	get_status(t_mtx *mutex, bool *val, t_data *data)
{
	bool	ret;

	operate_mutex(mutex, OP_LOCK, data);
	ret = *val;
	operate_mutex(mutex, OP_UNLOCK, data);
	return (ret);
}

void	set_timer(t_mtx *mutex, t_ul *dst, t_ul val, t_data *data)
{
	operate_mutex(mutex, OP_LOCK, data);
	*dst = val;
	operate_mutex(mutex, OP_UNLOCK, data);
}

t_ul	get_timer(t_mtx *mutex, t_ul *val, t_data *data)
{
	t_ul	ret;

	operate_mutex(mutex, OP_LOCK, data);
	ret = *val;
	operate_mutex(mutex, OP_UNLOCK, data);
	return (ret);
}
