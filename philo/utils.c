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

#include "philo.h"

int	print_usage(int errcode)
{
	printf("%s%s%s", RB, "Error: ", T);
	printf("%s%s%s", Y, MSG_ARGC, T);
	printf("%s%s%s", RB, "Example: ", T);
	printf("%s%s%s", P, MSG_EXAM, T);
	printf("%s%s%s", G, MSG_HELP, T);
	return (errcode);
}

int	free_mem(int errcode, t_data *data, char *msg)
{
	if (msg != NULL)
		log_error(FAILURE, msg, "", "");
	if (!data)
		return (errcode);
	free(data->input);
	free(data->phils);
	free(data->forks);
	return (errcode);
}
