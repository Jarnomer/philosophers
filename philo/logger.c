/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/26 08:14:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(int id, t_ul msec, t_state flg)
{
	if (flg == ST_TAKE)
		printf("%s%-5lu %s%d %s%shas taken fork\n%s",
			P, msec, CB, id, T, G, T);
	else if (flg == ST_EATING)
		printf("%s%-5lu %s%d %s%sis eating\n%s",
			P, msec, CB, id, T, G, T);
	else if (flg == ST_SLEEP)
		printf("%s%-5lu %s%d %s%sis sleeping\n%s",
			P, msec, CB, id, T, G, T);
	else if (flg == ST_THINK)
		printf("%s%-5lu %s%d %s%sis thinking\n%s",
			P, msec, CB, id, T, G, T);
	else if (flg == ST_DEATH)
		printf("%s%-5lu %s%d %sdied\n%s",
			P, msec, CB, id, RB, T);
}

void	log_status(t_philo *phil, t_state flg)
{
	if (process_finished(phil->data)
		|| process_error(phil->data))
		return ;
	operate_mutex(&phil->data->mutex[MX_LOG], OP_LOCK, phil->data);
	print_message(phil->id, phil->data->start, flg);
	operate_mutex(&phil->data->mutex[MX_LOG], OP_UNLOCK, phil->data);
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
