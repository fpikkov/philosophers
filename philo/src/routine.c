/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:43:34 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/03 12:43:36 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	thread_create(t_info *info, int64_t idx)
{
	if (info->count == 1)
	{
		if (pthread_create(&info->philos[idx].thread, NULL, \
		philo_single, (void *)(&info->philos[idx])) != 0)
		{
			destroy_threads(info, idx);
			return (false);
		}
	}
	else
	{
		if (pthread_create(&info->philos[idx].thread, NULL, \
		philo_routine, (void *)(&info->philos[idx])) != 0)
		{
			destroy_threads(info, idx);
			return (false);
		}
	}
	return (true);
}

bool	start_routines(t_info *info)
{
	int64_t	idx;

	idx = 0;
	if (!info)
		return (false);
	info->start_time = time_in_ms() + (info->count * START_MULTIPLIER);
	while (idx < info->count)
	{
		if (!thread_create(info, idx))
			return (false);
		idx++;
	}
	monitor_routine(info);
	return (true);
}
