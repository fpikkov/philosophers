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

static bool	has_philo_died(t_info *info, int32_t idx)
{
	size_t	current;

	current = time_in_ms() - info->philos[idx].timer_last_meal;
	if (current >= info->philos[idx].death_time \
	&& (info->philos[idx].eat_amount > 0 \
	|| info->philos[idx].eat_amount == -1))
	{
		pthread_mutex_lock(&info->halt_sim);
		info->halt = true;
		pthread_mutex_unlock(&info->halt_sim);
		return (true);
	}
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
		if (info->philos[idx].eat_amount > 0)
			return (false);
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
	usleep(5);
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
			idx++;
		}
		if (have_philos_eaten(info))
			break ;
	}
	return (NULL);
}
