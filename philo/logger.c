/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/27 17:29:25 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(int id, t_ul time, t_state state)
{
	if (state == ST_TAKE)
		printf("%s%-5lu %s%d %s%shas taken fork\n%s",
			P, time, CB, id, T, G, T);
	else if (state == ST_EAT)
		printf("%s%-5lu %s%d %s%sis eating\n%s",
			P, time, CB, id, T, G, T);
	else if (state == ST_SLEEP)
		printf("%s%-5lu %s%d %s%sis sleeping\n%s",
			P, time, CB, id, T, G, T);
	else if (state == ST_THINK)
		printf("%s%-5lu %s%d %s%sis thinking\n%s",
			P, time, CB, id, T, G, T);
	else if (state == ST_DEATH)
		printf("%s%-5lu %s%d %sdied\n%s",
			P, time, CB, id, RB, T);
}

void	log_status(t_philo *phil, t_state state)
{
	t_data	*data;
	t_ul	elapsed;

	data = phil->data;
	if (process_finished(data) || process_error(data))
		return ;
	operate_mutex(&phil->data->mutex[MX_LOG], OP_LOCK, data);
	set_timer(&data->mutex[MX_TIME], &elapsed,
		update_time(OP_MSEC, data) - data->start, data);
	print_message(phil->id, elapsed, state);
	operate_mutex(&phil->data->mutex[MX_LOG], OP_UNLOCK, data);
}

int	log_usage(int errcode)
{
	printf("%s%s%s", RB, "Error: ", T);
	printf("%s%s%s", Y, MSG_ARGC, T);
	printf("%s%s%s", RB, "Example: ", T);
	printf("%s%s%s", P, MSG_EXAM, T);
	printf("%s%s%s", G, MSG_HELP, T);
	return (errcode);
}
