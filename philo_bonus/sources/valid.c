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

#include <philo.h>

static inline int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

long	ft_atol(const char *str)
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

static int	valid_chars(const char *str)
{
	int	i;

	if (!str || !*str)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	valid_args(int argc, char **argv)
{
	while (--argc != 0)
	{
		if (valid_chars(argv[argc]) == -1 || ft_atol(argv[argc]) == -1)
			return (log_error(ERR_ARGV, argv[argc], ": ", MSG_ARGV));
	}
	return (0);
}
