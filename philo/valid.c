/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:11:28 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/25 17:44:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

long	custom_atol(const char *str)
{
	long	num;
	long	sgn;

	num = 0;
	sgn = 1;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str++ - '0';
		if (num > INT_MAX)
			return (FAILURE);
	}
	return (num * sgn);
}

static int	valid_chars(const char *str)
{
	int	i;

	if (!*str)
		return (FAILURE);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	valid_args(int ac, char **av)
{
	while (--ac != 0)
	{
		if (valid_chars(av[ac]) == FAILURE
			|| custom_atol(av[ac]) == FAILURE)
			return (log_error(EINVAL, av[ac], ": ", MSG_ARGV));
	}
	if ((ac == 6 && !custom_atol(av[ac - 1]))
		|| !custom_atol(av[1]))
		return (log_error(EINVAL, MSG_CNT, "", ""));
	return (SUCCESS);
}
