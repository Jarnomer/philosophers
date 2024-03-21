/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/08 15:21:03 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(int id, t_ul time, t_state state, t_data *data)
{
	if (state == ST_TAKE)
		printf("|%s  %-5lu %s|%s   %-3d %s|   %-3shas taken fork%s\t|\n",
			P, time, T, CB, id, T, G, T);
	else if (state == ST_EAT)
		printf("|%s  %-5lu %s|%s   %-3d %s|   %-3sis eating%s\t\t|\n",
			P, time, T, CB, id, T, G, T);
	else if (state == ST_SLP)
		printf("|%s  %-5lu %s|%s   %-3d %s|   %-3sis sleeping%s\t|\n",
			P, time, T, CB, id, T, G, T);
	else if (state == ST_THK)
		printf("|%s  %-5lu %s|%s   %-3d %s|   %-3sis thinking%s\t|\n",
			P, time, T, CB, id, T, G, T);
	else if (state == ST_DIE)
		printf("|%s  %-5lu %s|%s   %-3d %s|   %-3sdied\t\t%s|\n",
			P, time, T, CB, id, T, RB, T);
	else if (state == ST_FULL)
		printf("|%s  %-5lu %s|%s   %-3d %s|   %-3sis full%s\t\t|\n",
			P, time, T, CB, id, T, BB, T);
	else
	{
		log_error(FAILURE, MSG_STAT, "<print_message>", "");
		error_occured(data, EXIT_FAILURE);
	}
}

void	log_status(t_philo *phil, t_state state)
{
	t_data	*data;
	t_ul	uptime;

	data = phil->data;
	uptime = get_timer(&data->uptime, &data->mutex[MX_EPCH], data);
	operate_mutex(&data->mutex[MX_LOG], OP_LOCK, data);
	if (!process_finished(data) && !process_failed(data))
		print_message(phil->id, uptime, state, data);
	operate_mutex(&data->mutex[MX_LOG], OP_UNLOCK, data);
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
	ft_putstr_fd(RB, STDERR_FILENO);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(T, STDERR_FILENO);
	ft_putstr_fd(Y, STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	ft_putstr_fd(T, STDERR_FILENO);
	return (errcode);
}
