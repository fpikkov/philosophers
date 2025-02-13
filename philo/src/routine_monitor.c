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

	pthread_mutex_lock(&info->meals[idx / 10]);
	if (info->philos[idx].timer_last_meal == 0)
	{
		pthread_mutex_unlock(&info->meals[idx / 10]);
		return (false);
	}
	current = time_in_ms(info->start_time) - info->philos[idx].timer_last_meal;
	if (current > info->philos[idx].death_time \
	&& (info->philos[idx].eat_amount > 0 \
	|| info->philos[idx].eat_amount == -1))
	{
		pthread_mutex_lock(&info->halt_sim);
		info->halt = true;
		pthread_mutex_unlock(&info->halt_sim);
		pthread_mutex_unlock(&info->meals[idx / 10]);
		return (true);
	}
	pthread_mutex_unlock(&info->meals[idx / 10]);
	return (false);
}

static bool	have_philos_eaten(t_info *info)
{
	size_t	idx;

	idx = 0;
	if (!(info->should_eat))
		return (false);
	while (idx < info->count)
	{
		pthread_mutex_lock(&info->meals[idx / 10]);
		if (info->philos[idx].eat_amount > 0)
		{
			pthread_mutex_unlock(&info->meals[idx / 10]);
			return (false);
		}
		pthread_mutex_unlock(&info->meals[idx / 10]);
		idx++;
	}
	pthread_mutex_lock(&info->halt_sim);
	info->halt = true;
	pthread_mutex_unlock(&info->halt_sim);
	return (true);
}

void	monitor_routine(t_info *info)
{
	size_t	idx;

	info->start = true;
	usleep(500);
	while (true)
	{
		idx = 0;
		while (idx < info->count)
		{
			if (has_philo_died(info, idx))
			{
				log_death(info, idx);
				return ;
			}
			idx++;
		}
		if (have_philos_eaten(info))
			break ;
	}
}
