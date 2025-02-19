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

static void	event_fancy(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->printing);
	if (state == DEATH)
		printf("💀 %-16ld\t[%ld] died\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == THINKING && !(*philo->halt))
		printf("🤔 %-16ld\t[%ld] is thinking\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == EATING && !(*philo->halt))
		printf("😋 %-16ld\t[%ld] is eating\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == SLEEPING && !(*philo->halt))
		printf("🥱 %-16ld\t[%ld] is sleeping\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == FORK && !(*philo->halt))
		printf("🍴 %-16ld\t[%ld] has taken a fork\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(philo->printing);
}

static void	event_standard(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->printing);
	if (state == DEATH)
		printf("%ld %ld died\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == THINKING && !(*philo->halt))
		printf("%ld %ld is thinking\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == EATING && !(*philo->halt))
		printf("%ld %ld is eating\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == SLEEPING && !(*philo->halt))
		printf("%ld %ld is sleeping\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == FORK && !(*philo->halt))
		printf("%ld %ld has taken a fork\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(philo->printing);
}

void	log_event(t_philo *philo, t_state state)
{
	if (DEBUG)
		event_fancy(philo, state);
	else
		event_standard(philo, state);
}
