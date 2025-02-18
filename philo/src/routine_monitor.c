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

static bool	has_philo_died(t_info *info, size_t idx)
{
	size_t	current;

	pthread_mutex_lock(&info->meals[idx]);
	if (info->philos[idx].timer_last_meal == 0)
		return (safe_unlock(&info->meals[idx], false));
	current = time_in_ms(0) - info->philos[idx].timer_last_meal;
	if (current > info->philos[idx].death_time \
	&& (info->philos[idx].eat_amount > 0 \
	|| info->philos[idx].eat_amount == -1))
	{
		pthread_mutex_lock(&info->halt_sim);
		info->halt = true;
		pthread_mutex_unlock(&info->halt_sim);
		return (safe_unlock(&info->meals[idx], true));
	}
	return (safe_unlock(&info->meals[idx], false));
}

static bool	have_philos_eaten(t_info *info)
{
	size_t	idx;

	idx = 0;
	if (!(info->should_eat))
		return (false);
	while (idx < info->count)
	{
		pthread_mutex_lock(&info->meals[idx]);
		if (info->philos[idx].eat_amount > 0)
			return (safe_unlock(&info->meals[idx], false));
		pthread_mutex_unlock(&info->meals[idx]);
		idx++;
	}
	pthread_mutex_lock(&info->halt_sim);
	info->halt = true;
	return (safe_unlock(&info->halt_sim, true));
}

static void	set_start_time(t_info *info)
{
	size_t	start;
	size_t	idx;

	idx = 0;
	start = time_in_ms(0);
	info->start_time = start;
	while (idx < info->count)
		info->philos[idx++].start_time = start;
}

void	monitor_routine(t_info *info)
{
	size_t	idx;

	set_start_time(info);
	info->start = true;
	usleep(500);
	while (true)
	{
		idx = 0;
		while (idx < info->count)
		{
			if (has_philo_died(info, idx))
			{
				log_event(&info->philos[idx], DEATH);
				return ;
			}
			idx++;
		}
		if (have_philos_eaten(info))
			break ;
	}
}
