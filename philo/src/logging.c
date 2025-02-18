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

/* void	log_death(t_info *info, size_t num)
{
	pthread_mutex_lock(&info->printing);
	printf("💀 %-16ld\t[%ld] died\n", time_in_ms(info->start_time), num);
	pthread_mutex_unlock(&info->printing);
}

void	log_event(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->printing);
	if (state == THINKING && !(*philo->halt))
		printf("🤔 %-16ld\t[%ld] is thinking\n", \
		time_in_ms(philo->start_time), philo->id);
	else if (state == EATING && !(*philo->halt))
		printf("😋 %-16ld\t[%ld] is eating\n", \
		time_in_ms(philo->start_time), philo->id);
	else if (state == SLEEPING && !(*philo->halt))
		printf("🥱 %-16ld\t[%ld] is sleeping\n", \
		time_in_ms(philo->start_time), philo->id);
	else if (state == FORK && !(*philo->halt))
		printf("🍴 %-16ld\t[%ld] has taken a fork\n", \
		time_in_ms(philo->start_time), philo->id);
	pthread_mutex_unlock(philo->printing);
} */

/**
 * @brief Converts the microsecond time to millisecond time.
 * @param[in] start the starting time of the simulation
 * @return Current time in unsigned long representation of milliseconds.
 */
size_t	time_in_ms(size_t start)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time - start);
}

/**
 * @brief Takes in time in milliseconds an sleeps for that amount of time.
 * @param[in] begin Time since the beginning of the simulation
 * @param[in] msec Time in milliseconds
 * @param[in] halt Pointer to the atomic which tells if the sim should stop
 */
void	sleep_for_ms(size_t begin, size_t msec, _Atomic bool *halt)
{
	size_t	start;

	if (msec == 0 || begin == 0)
		return ;
	start = time_in_ms(begin);
	while (time_in_ms(begin) - start < msec)
	{
		if (*halt == true)
			break ;
		if ((msec - (time_in_ms(begin) - start)) > 1)
			usleep(50);
		else
			while (time_in_ms(begin) - start < msec)
				continue ;
	}
}

void	log_death(t_info *info, size_t num)
{
	pthread_mutex_lock(&info->printing);
	printf("%ld %ld died\n", time_in_ms(info->start_time), num);
	pthread_mutex_unlock(&info->printing);
}

void	log_event(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->printing);
	if (state == THINKING && !(*philo->halt))
		printf("%ld %ld is thinking\n", \
		time_in_ms(philo->start_time), philo->id);
	else if (state == EATING && !(*philo->halt))
		printf("%ld %ld is eating\n", \
		time_in_ms(philo->start_time), philo->id);
	else if (state == SLEEPING && !(*philo->halt))
		printf("%ld %ld is sleeping\n", \
		time_in_ms(philo->start_time), philo->id);
	else if (state == FORK && !(*philo->halt))
		printf("%ld %ld has taken a fork\n", \
		time_in_ms(philo->start_time), philo->id);
	pthread_mutex_unlock(philo->printing);
}
