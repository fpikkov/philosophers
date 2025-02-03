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
 * *** QUESTIONS ***
 *
 * 1. Will they be thinking for an unspecified amount of time
 *  as they wait for the forks to open up?
 * 2. How to update the timers on all threads automagically?
 * 3. With the optional argument, will the timers still be counting
 *  while the philosopher waits for others to finish up eating?
 */
/**
 * *** PROGRAM LOGS ***
 *
 * 1.  Any state change of a philosopher must be formatted as follows :
 * 		- timestamp_in_ms X has taken a fork
 * 		- timestamp_in_ms X is eating
 * 		- timestamp_in_ms X is sleeping
 * 		- timestamp_in_ms X is thinking
 * 		- timestamp_in_ms X died
 * 2. A displayed state message should not be mixed up with another message.
 * 3. Philosopher death should be displayed within 10 ms after the event.
 */

void	debug_parsing(t_info *info)
{
	int32_t	idx;
	int32_t	count;

	if (!info)
		return ;
	if (!info->philos)
		return ;
	idx = 0;
	count = info->count;
	while (idx < count)
	{
		printf("Philo ID[%i]: Halted[%i], State[%i], ", info->philos[idx].id,
			*(info->philos[idx].halt), info->philos[idx].state);
		printf("TtD[%i], TtE[%i], TtS[%i], EA[%i]\n",
			info->philos[idx].death_time,
			info->philos[idx].eat_time, info->philos[idx].sleep_time,
			info->philos[idx].eat_amount);
		idx++;
	}
}

/**
 * TODO: Remove debugging function
 */
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
	// -------- ROUTINES -------
	debug_parsing(info);
	// -------------------------
	destroy_mutexes(info, info->count, ALL);
	if (info)
		free_info(info);
	return (EXIT_SUCCESS);
}
