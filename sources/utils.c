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
	printf("%s%s%s", BOlD_RED, "Error: ", RESET);
	printf("%s%s%s", YELLOW, MSG_ARGC, RESET);
	printf("%s%s%s", BOlD_RED, "Example: ", RESET);
	printf("%s%s%s", BOLD_CYAN, MSG_EXAM, RESET);
	printf("%s%s%s", GREEN, MSG_HELP, RESET);
	return (errcode);
}

static inline int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

long	custom_atol(const char *str)
{
	long	num;

	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str++ - '0';
		if (num > INT_MAX)
			return (-1);
	}
	if (num == 0)
		return (-1);
	return (num);
}

void	process_free(t_data *data)
{
	if (!data)
		return ;
	free(data->input);
	free(data->philos);
	free(data->forks);
}

int	error_exit(int errcode, t_data *data, char *msg)
{
	log_error(errcode, msg, "", "");
	process_free(data);
	return (errcode);
}
