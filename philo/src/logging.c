/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:30:24 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/03 13:30:26 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_death(t_info *info, int32_t num)
{
	while (pthread_mutex_lock(&info->printing))
		usleep(1);
	printf("💀 <%ld>\t[%i] died\n", time_in_ms(), num);
	pthread_mutex_unlock(&info->printing);
}

void	log_event(t_philo *philo, t_state state)
{
	while (pthread_mutex_lock(philo->printing))
		usleep(5);
	if (state == THINKING)
		printf("🤔 <%ld>\t[%i] is thinking\n", time_in_ms(),philo->id);
	else if (state == EATING)
		printf("😋 <%ld>\t[%i] is eating\n", time_in_ms(), philo->id);
	else if (state == SLEEPING)
		printf("🥱 <%ld>\t[%i] is sleeping\n", time_in_ms(), philo->id);
	pthread_mutex_unlock(philo->printing);
}

/**
 * @brief Converts the microsecond time to millisecond time.
 * @return Current time in unsigned long representation of milliseconds.
 */
size_t	time_in_ms(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

/**
 * @brief Takes in time in milliseconds an sleeps for that amount of time.
 * @param[in] msec Time in milliseconds
 */
void	sleep_for_ms(int32_t msec)
{
	uint32_t	usec;

	usec = ((uint32_t)msec * 1000);
	usleep(usec);
}
