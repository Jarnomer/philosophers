/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:50:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/21 11:50:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	print_usage(int errcode)
{
	printf("%s%s%s", BOLD_RED, "Error: ", RESET);
	printf("%s%s%s", YELLOW, MSG_ARGC, RESET);
	printf("%s%s%s", BOLD_RED, "Example: ", RESET);
	printf("%s%s%s", BOLD_CYAN, MSG_EXAM, RESET);
	printf("%s%s%s", GREEN, MSG_HELP, RESET);
	return (errcode);
}

void	precise_sleep(int target_time, t_data *data)
{
	long	start;
	long	current;

	start = operate_timer(OP_MSEC, data);
	while (1)
	{
		current = operate_timer(OP_MSEC, data);
		if (current - start >= target_time)
			break ;
		usleep(500);
	}
}

void	error_exit(int errcode, t_data *data, char *msg)
{
	log_error(errcode, msg, "", "");
	process_free(data);
	exit(errcode);
}
