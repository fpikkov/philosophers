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

void	log_death(t_info *info, size_t num)
{
	pthread_mutex_lock(&info->printing);
	printf("💀 <%ld>\t[%ld] died\n", time_in_ms(), num);
	pthread_mutex_unlock(&info->printing);
}

void	log_event(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->printing);
	if (state == THINKING && !(*philo->halt))
		printf("🤔 <%ld>\t[%ld] is thinking\n", time_in_ms(),philo->id);
	else if (state == EATING && !(*philo->halt))
		printf("😋 <%ld>\t[%ld] is eating\n", time_in_ms(), philo->id);
	else if (state == SLEEPING && !(*philo->halt))
		printf("🥱 <%ld>\t[%ld] is sleeping\n", time_in_ms(), philo->id);
	else if (state == FORK && !(*philo->halt))
		printf("🍴 <%ld>\t[%ld] has taken a fork\n", time_in_ms(), philo->id);
	pthread_mutex_unlock(philo->printing);
}

/**
 * @brief Converts the microsecond time to millisecond time.
 * @return Current time in unsigned long representation of milliseconds.
 */
size_t	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Takes in time in milliseconds an sleeps for that amount of time.
 * @param[in] msec Time in milliseconds
 */
void	sleep_for_ms(size_t msec)
{
	uint32_t	usec;

	usec = (msec * 1000);
	usleep(usec);
}
