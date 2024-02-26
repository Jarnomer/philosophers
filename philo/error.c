/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:14:09 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/25 20:50:33 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	log_error(int errcode, char *s1, char *s2, char *s3)
{
	ft_putstr_fd(RB, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(T, 2);
	ft_putstr_fd(Y, 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	ft_putstr_fd(T, 2);
	return (errcode);
}
