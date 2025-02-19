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
 * @return int64_t current time in milliseconds.
 */
int64_t	time_in_ms(void)
{
	t_time	tv;

	memset(&tv, 0, sizeof(t_time));
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Takes in time in milliseconds an sleeps for that amount of time.
 * @param[in] msec Time in milliseconds
 * @param[in] halt Pointer to the atomic which tells if the sim should stop
 */
void	sleep_for_ms(int64_t msec, _Atomic bool *halt)
{
	int64_t	start;

	if (msec == 0)
		return ;
	start = time_in_ms();
	while (time_in_ms() - start < msec)
	{
		if (*halt == true)
			break ;
		if ((msec - (time_in_ms() - start)) > 2)
			usleep(SLEEP_USEC);
		else
			while (time_in_ms() - start < msec)
				continue ;
	}
}
