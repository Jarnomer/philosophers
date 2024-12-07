/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:38:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/28 19:12:27 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>

# define MSG_ARGC	"Number of argments must be 4 or 5\n"
# define MSG_ARGV	"Is invalid argument"

# define MSG_SYSC	"System call error in "
# define MSG_OPER	"Invalid operator in "
# define MSG_STAT	"Invalid state in "
# define MSG_MEM	"Out of memory"

# define MSG_EXAM	"./philo 2 610 300 200 (3)\n"
# define MSG_HELP	"\
[2]:\t<number of philosophers>\n\
[610]:\t<time to die>\n\
[300]:\t<time to eat>\n\
[200]:\t<time to sleep>\n\
[3]:\t<number of meals>\n"

# define BOlD_RED	"\033[1;31m"
# define BOLD_CYAN	"\033[1;36m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define RESET		"\033[0m"

enum e_exitcodes
{
	NOERROR,
	ERR_ARGC,
	ERR_ARGV,
	ERR_SYSC,
	ERR_STAT,
	ERR_OPER,
	ERR_MEM,
};

#endif
