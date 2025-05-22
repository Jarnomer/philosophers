/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/04 17:27:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	threads_synchronized(t_data *data)
{
	set_status(&data->stat[ST_SYNC], true, &data->mutex[MX_SYNC], data);
}

void	threads_spinlocked(t_data *data)
{
	while (!get_status(&data->stat[ST_SYNC], &data->mutex[MX_SYNC], data))
		true ;
}

bool	process_finished(t_data *data)
{
	return (get_status(&data->stat[ST_DONE], &data->mutex[MX_DONE], data));
}

bool	process_failed(t_data *data)
{
	return (get_status(&data->stat[ST_ERR], &data->mutex[MX_ERR], data));
}

void	process_failure(t_data *data, int errcode)
{
	operate_mutex(&data->mutex[MX_ERR], OP_LOCK, data);
	data->stat[ST_ERR] = true;
	if (data->exitcode == 0)
		data->exitcode = errcode;
	operate_mutex(&data->mutex[MX_ERR], OP_UNLOCK, data);
}
