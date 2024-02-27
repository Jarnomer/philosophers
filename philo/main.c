/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:31:56 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/25 20:01:36 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (log_usage(EXIT_FAILURE));
	if (valid_args(argc, argv) != SUCCESS)
		return (EINVAL);
	if (init_data(&data, argc, argv) != SUCCESS)
		return (ENOMEM);
	if (process_manager(&data) != SUCCESS)
		return (data.excode);
	return (EXIT_SUCCESS);
}
