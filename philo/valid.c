/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:11:28 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/30 19:59:11 by jmertane         ###   ########.fr       */
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

	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str++ - '0';
		if (num > INT_MAX)
			return (FAILURE);
	}
	if (!num)
		return (FAILURE);
	return (num);
}

static int	valid_chars(const char *str)
{
	int	i;

	if (!str || !*str)
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
		{
			log_error(FAILURE, av[ac], ": ", MSG_ARGV);
			return (EINVAL);
		}
	}
	return (SUCCESS);
}
