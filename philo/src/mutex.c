/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:52:51 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 13:52:52 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_meals(t_info *info)
{
	int64_t	idx;

	if (!info)
		return (false);
	idx = 0;
	while (idx < info->count)
	{
		if (pthread_mutex_init(&info->meals[idx], NULL) != 0)
		{
			destroy_mutexes(info, idx, MEAL);
			return (false);
		}
		idx++;
	}
	return (true);
}

/**
 * @brief Initializes all the mutexes.
 * On failure will destroy the previously initialized mutexes.
 * @return true if successful, otherwise false
 */
bool	init_mutexes(t_info *info)
{
	int64_t	idx;

	idx = 0;
	if (!info)
		return (false);
	while (idx < info->count)
	{
		if (pthread_mutex_init(&info->forks[idx], NULL) != 0)
			return (destroy_mutexes(info, idx, FORKS), false);
		idx++;
	}
	if (pthread_mutex_init(&info->halt_sim, NULL) != 0)
		return (destroy_mutexes(info, idx, FORKS), false);
	if (pthread_mutex_init(&info->printing, NULL) != 0)
		return (destroy_mutexes(info, idx, FORKS | DEAD), false);
	if (!init_meals(info))
		return (destroy_mutexes(info, idx, FORKS | DEAD | PRINT), false);
	return (true);
}

/* bool	check_halt(t_info *info)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&info->halt_sim);
	if (info->halt == true)
		ret = true;
	pthread_mutex_unlock(&info->halt_sim);
	return (ret);
} */
