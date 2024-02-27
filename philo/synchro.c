/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/26 19:19:05 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	synchronize_threads(t_data *data)
{
	set_status(&data->mutex[MX_SYNC],
		&data->stat[ST_SYNC], true, data);
}

void	spinlock_threads(t_data *data)
{
	while (!get_status(&data->mutex[MX_SYNC],
			&data->stat[ST_SYNC], data))
		true ;
}

bool	process_finished(t_data *data)
{
	return (get_status(&data->mutex[MX_DONE],
			&data->stat[ST_DONE], data));
}

bool	process_error(t_data *data)
{
	return (get_status(&data->mutex[MX_ERR],
			&data->stat[ST_ERR], data));
}

void	error_occured(t_data *data, int errcode)
{
	operate_mutex(&data->mutex[MX_ERR], OP_LOCK, data);
	data->stat[ST_ERR] = true;
	if (data->excode == SUCCESS)
		data->excode = errcode;
	operate_mutex(&data->mutex[MX_ERR], OP_UNLOCK, data);
}
