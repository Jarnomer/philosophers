/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:33:17 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/22 17:18:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_time_error(int excode)
{
	if (excode == EFAULT)
		return ("Pointer outside the accessible address space.");
	else if (excode == EINVAL)
		return ("Timezone or something else is invalid.");
	else
		return ("The calling process has insufficient privilege");
}

long	refresh_time(t_data *data)
{
	struct timeval	tp;

	data->excode = gettimeofday(&tp, NULL);
	if (data->excode != SUCCESS)
		return (error_logger(FAILURE,
				MSG_SYSC, "<gettimeofday>: ",
				get_time_error(data->excode)));
	return ((tp.tv_sec * 1e3) + (tp.tv_usec / 1e3));
}
