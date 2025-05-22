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

#include <philo.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_usage(ERR_ARGC));
	if (valid_args(argc, argv) != 0)
		return (ERR_ARGV);
	if (init_data(&data, argc, argv) != 0)
		return (ERR_MEM);
	if (run_simulation(&data) != 0)
		return (data.exitcode);
	return (NOERROR);
}
