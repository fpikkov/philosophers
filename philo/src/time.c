/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:55:39 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/16 12:05:40 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Converts the microsecond time to millisecond time.
 * Start may be left as zero to get the absolute time.
 * @param[in] start the starting time of the simulation
 * @return Current time in unsigned long representation of milliseconds.
 */
size_t	time_in_ms(size_t start)
{
	t_time	tv;
	size_t	time;

	memset(&tv, 0, sizeof(t_time));
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (start != 0)
		return (time - start);
	return (time);
}

/**
 * @brief Takes in time in milliseconds an sleeps for that amount of time.
 * @param[in] msec Time in milliseconds
 * @param[in] halt Pointer to the atomic which tells if the sim should stop
 */
void	sleep_for_ms(size_t msec, _Atomic bool *halt)
{
	size_t	start;

	if (msec == 0)
		return ;
	start = time_in_ms(0);
	while (time_in_ms(0) - start < msec)
	{
		if (*halt == true)
			break ;
		if ((msec - (time_in_ms(0) - start)) > 2)
			usleep(50);
		else
			while (time_in_ms(0) - start < msec)
				continue ;
	}
}
