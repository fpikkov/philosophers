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
	t_info	info;

	if (argc < 5 || argc > 6)
		return (print_error(MISSING_ARGS, true));
	if (!parse_args(&info, argc, argv))
		return (EXIT_FAILURE);
	if (start_routines(&info))
		destroy_threads(&info, info.count);
	destroy_mutexes(&info, info.count, ALL);
	free_info(&info);
	return (EXIT_SUCCESS);
}
