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
		if (valid_chars(argv[argc]) == -1 || custom_atol(argv[argc]) == -1)
			return (log_error(ERR_ARGV, argv[argc], ": ", MSG_ARGV));
	}
	return (0);
}
