/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:27:32 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/05 11:27:35 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	has_died(t_philo *philo)
{
	int64_t	current;

	if (philo->eat_amount == 0)
		return (false);
	current = time_in_ms() - philo->last_meal;
	if (current >= philo->info->death_time)
	{
		pthread_mutex_lock(&philo->info->halt_sim);
		philo->info->halt = true;
		log_event(philo, DEATH);
		pthread_mutex_unlock(&philo->info->halt_sim);
		pthread_mutex_unlock(philo->meal);
		return (true);
	}
	return (false);
}

static bool	check_philos(t_info *info)
{
	bool	full;
	int64_t	idx;

	full = true;
	idx = 0;
	while (idx < info->count)
	{
		pthread_mutex_lock(&info->meals[idx]);
		if (has_died(&info->philos[idx]))
			return (true);
		if (info->should_eat)
			if (info->philos[idx].eat_amount > 0)
				full = false;
		pthread_mutex_unlock(&info->meals[idx]);
		idx++;
	}
	if (info->should_eat && full)
	{
		pthread_mutex_lock(&info->halt_sim);
		info->halt = true;
		pthread_mutex_unlock(&info->halt_sim);
		return (true);
	}
	return (false);
}

void	monitor_routine(t_info *info)
{
	while (time_in_ms() < info->start_time)
		continue ;
	while (true)
	{
		if (check_philos(info))
			return ;
		usleep(MONITOR_COOLDOWN);
	}
}
