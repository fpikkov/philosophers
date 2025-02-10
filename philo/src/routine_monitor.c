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

	pthread_mutex_lock(&info->meal);
	if (info->philos[idx].timer_last_meal == 0)
	{
		pthread_mutex_unlock(&info->meal);
		return (false);
	}
	current = time_in_ms() - info->philos[idx].timer_last_meal;
	if (current > info->philos[idx].death_time \
	&& (info->philos[idx].eat_amount > 0 \
	|| info->philos[idx].eat_amount == -1))
	{
		pthread_mutex_lock(&info->halt_sim);
		info->halt = true;
		pthread_mutex_unlock(&info->halt_sim);
		pthread_mutex_unlock(&info->meal);
		return (true);
	}
	pthread_mutex_unlock(&info->meal);
	return (false);
}

static bool	have_philos_eaten(t_info *info)
{
	size_t	idx;

	idx = 0;
	if (info->philos[idx].eat_amount == -1)
		return (false);
	while (idx < info->count)
	{
		pthread_mutex_lock(&info->meal);
		if (info->philos[idx].eat_amount > 0)
		{
			pthread_mutex_unlock(&info->meal);
			return (false);
		}
		pthread_mutex_unlock(&info->meal);
		idx++;
	}
	pthread_mutex_lock(&info->halt_sim);
	info->halt = true;
	pthread_mutex_unlock(&info->halt_sim);
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_info	*info;
	size_t	idx;

	info = (t_info *)arg;
	info->start = true;
	usleep(500);
	while (!info->halt)
	{
		idx = 0;
		while (idx < info->count)
		{
			if (has_philo_died(info, idx))
			{
				log_death(info, idx);
				return (NULL);
			}
			usleep(100);
			idx++;
		}
		if (have_philos_eaten(info))
			break ;
	}
	return (NULL);
}
