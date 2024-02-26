/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutacc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:20 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/26 08:10:06 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutate_status(t_mtx *mutex, bool *dst, bool val, t_data *data)
{
	operate_mutex(mutex, OP_LOCK, data);
	*dst = val;
	operate_mutex(mutex, OP_UNLOCK, data);
}

bool	access_status(t_mtx *mutex, bool *val, t_data *data)
{
	bool	ret;

	operate_mutex(mutex, OP_LOCK, data);
	ret = *val;
	operate_mutex(mutex, OP_UNLOCK, data);
	return (ret);
}

void	mutate_timer(t_mtx *mutex, t_ul *dst, t_ul val, t_data *data)
{
	operate_mutex(mutex, OP_LOCK, data);
	*dst = val;
	operate_mutex(mutex, OP_UNLOCK, data);
}

t_ul	access_timer(t_mtx *mutex, t_ul *val, t_data *data)
{
	t_ul	ret;

	operate_mutex(mutex, OP_LOCK, data);
	ret = *val;
	operate_mutex(mutex, OP_UNLOCK, data);
	return (ret);
}
