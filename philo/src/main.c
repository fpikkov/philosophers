/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:52:32 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 13:52:34 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info		*info;

	if (argc < 5 || argc > 6)
		return (print_error(MISSING_ARGS));
	info = parse_args(argc, argv);
	if (!info)
		return (print_error(PARSE_FAILURE));
	if (!init_mutexes(info))
	{
		free_info(info);
		return (print_error(THREAD_FAILURE));
	}
	if (start_routines(info) == true)
		destroy_threads(info, info->count);
	destroy_mutexes(info, info->count, ALL);
	if (info)
		free_info(info);
	return (EXIT_SUCCESS);
}
