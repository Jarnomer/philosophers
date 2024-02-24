/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:14:09 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/23 09:29:35 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_out(int errcode, t_data *data, char *msg)
{
	if (msg != NULL)
		error_logger(FAILURE, msg, "", "");
	if (!data)
		return (errcode);
	free(data->input);
	free(data->phils);
	free(data->forks);
	return (errcode);
}

static int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		++len;
	return (len);
}

static inline void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	error_logger(int errcode, char *s1, char *s2, char *s3)
{
	ft_putstr_fd(BOLD_RED, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd(YELLOW, 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	ft_putstr_fd(RESET, 2);
	return (errcode);
}

int	print_usage(int errcode)
{
	printf("%s%s%s", BOLD_RED, "Error: ", RESET);
	printf("%s%s%s", YELLOW, MSG_ARGC, RESET);
	printf("%s%s%s", BOLD_RED, "Example: ", RESET);
	printf("%s%s%s", PURPLE, MSG_EXAM, RESET);
	printf("%s%s%s", GREEN, MSG_HELP, RESET);
	return (errcode);
}
