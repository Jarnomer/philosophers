/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:22:38 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/30 19:38:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline long	convert_to_micro_second(long target)
{
	return (target *= 1000);
}

static inline long	gettime(long start, t_data *data)
{
	return (operate_timer(OP_USEC, data) - start);
}

void	percision_sleep(long target, t_data *data)
{
	long	start;

	target = convert_to_micro_second(target);
	start = operate_timer(OP_USEC, data);
	while (gettime(start, data) < target)
	{
		if (process_finished(data) || process_failed(data))
			break ;
		usleep(500);
	}
}
