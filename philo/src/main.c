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

/**
 * *** PSEUDOCODE ***
 *
 * 1. Parse args so you can get the integers for each arg.
 *     Consider argc[6] exit conditions if it exists.
 * 2. Create threads for each philospher. (Do philos get their own structs/ LL?)
 * 3. Create equal amount of forks through mutex.
 * 4. Run sim: eat > sleep > think > eat
 * 5. (a) Uneven no. philos will grab a fork to their left AND THEN the right.
 *         Evem no. philos will do so in opposite order. Asymmetry prevents deadlock.
 *    (b) Alternatively implement a multithreading solution to avoid deadlock.
 * 6. Exit program and free resources once a philo dies or they have eaten enough.
 */

int	main(int argc, char **argv)
{
	t_info		*info;

	if (argc < 5 || argc > 6)
		return (print_error(MISSING_ARGS));
	info = parse_args(argc, argv);
	if (!info)
		return (print_error(PARSE_FAILURE));
	if (!alloc_threads(info))
		return (print_error(THREAD_FAILURE));
	// Rest of the code

	if (info)
		free_info(info);
	return (EXIT_SUCCESS);
}
