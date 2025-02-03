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
	struct timeval	tv;

	pthread_mutex_lock(&info->printing);
	gettimeofday(&tv, NULL);
	printf("💀 [%ld] \t[%i] died\n",tv.tv_usec, num);
	pthread_mutex_unlock(&info->printing);
	destroy_threads(info, info->count, true);
}

void	log_event(t_philo *philo, t_state state)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->printing);
	gettimeofday(&tv, NULL);
	if (state == THINKING)
		printf("🤔 [%ld] \t[%i] is thinking\n", tv.tv_usec, philo->id);
	else if (state == EATING)
		printf("😋 [%ld] \t[%i] is eating\n", tv.tv_usec, philo->id);
	else if (state == SLEEPING)
		printf("🥱 [%ld] \t[%i] is sleeping\n", tv.tv_usec, philo->id);
	pthread_mutex_unlock(philo->printing);
}
