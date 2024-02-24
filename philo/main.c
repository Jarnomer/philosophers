/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:31:56 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/24 15:23:49 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_usage(EXIT_FAILURE));
	if (valid_arguments(argc, argv) != SUCCESS)
		return (EINVAL);
	if (init_data(&data, argc, argv) != SUCCESS)
		return (ENOMEM);
	if (data.input->amount == 1
		|| data.input->meals == 0)
		return (free_out(SUCCESS, &data, NULL));
	if (start_simulation(&data) != SUCCESS)
		return (data.excode);
	return (EXIT_SUCCESS);
}
