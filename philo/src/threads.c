/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:52:51 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 13:52:52 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * *** PSEUDOCODE ***
 *
 * The potentially better way is to give each philo their own struct.
 * This will enable each one to have their own timers and eat counter.
 *
 * But then where to store each mutex fork?
 */
bool	alloc_threads(t_info *info)
{
	uint32_t	count;

	if (!info)
		return (false);
	count = info->count;
	info->philos = (pthread_t *)malloc(sizeof(pthread_t) * count);
	if (!info->philos)
		return (false);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	if (!info->forks)
	{
		if (info->philos)
			free(info->philos);
		free(info);
		return (false);
	}
	return (true);
}
