/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/01 15:13:10 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	print_message(int id, long time, t_state state, t_data *data)
{
	if (state == ST_TAKE)
		printf("%lu %d has taken fork\n", time, id);
	else if (state == ST_EAT)
		printf("%lu %d is eating\n", time, id);
	else if (state == ST_SLP)
		printf("%lu %d is sleeping\n", time, id);
	else if (state == ST_THK)
		printf("%lu %d is thinking\n", time, id);
	else if (state == ST_DIE)
		printf("%lu %d died\n", time, id);
	else
	{
		log_error(ERR_STAT, MSG_STAT, "<print_message>", "");
		process_failure(data, ERR_STAT);
	}
}

void	log_status(t_philo *philo, t_state state)
{
	t_data	*data;
	long	uptime;

	data = philo->data;
	uptime = get_timer(&data->uptime, &data->mutex[MX_EPCH], data);
	operate_mutex(&data->mutex[MX_LOG], OP_LOCK, data);
	if (!process_finished(data) && !process_failed(data))
		print_message(philo->id, uptime, state, data);
	operate_mutex(&data->mutex[MX_LOG], OP_UNLOCK, data);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

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
	ft_putstr_fd(BOlD_RED, STDERR_FILENO);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd(YELLOW, STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (errcode);
}
