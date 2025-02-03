/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:39 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 17:05:40 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_info(t_info *info)
{
	if (!info)
		return ;
	if (info->philos)
	{
		free(info->philos);
		info->philos = NULL;
	}
	if (info->forks)
	{
		free(info->forks);
		info->forks = NULL;
	}
	free(info);
	info = NULL;
}

void	destroy_mutexes(t_info *info, int32_t count, t_flags flag)
{
	int32_t	idx;

	idx = 0;
	if (!info || !count)
		return ;
	while (idx < count && (flag & FORKS))
	{
		pthread_mutex_destroy(&info->forks[idx]);
		idx++;
	}
	if (flag & DEAD)
		pthread_mutex_destroy(&info->halt_sim);
	if (flag & PRINT)
		pthread_mutex_destroy(&info->printing);
}

void	destroy_threads(t_info *info, int32_t count, bool monitor)
{
	int32_t	idx;

	idx = 0;
	if (monitor)
		pthread_join(info->monitor, NULL);
	while (idx < count)
	{
		pthread_join(info->philos[idx].thread, NULL);
		idx++;
	}
}
