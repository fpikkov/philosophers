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

/**
 * @brief Frees the allocated memory for the program
 * @param[in] info The master structure of the project
 */
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

/**
 * @brief Destroys mutexes based on flags and up to but not including count
 * @param[in] info Master structure of the project
 * @param[in] count How many mutexes to destroy
 * @param[in] flag Which mutex types to destroy
 */
void	destroy_mutexes(t_info *info, size_t count, t_flags flag)
{
	size_t	idx;

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
	if (flag & MEAL)
		pthread_mutex_destroy(&info->meal);
}

/**
 * @brief Destroys all threads by using pthread_join
 * @param[in] info Master struct of the project
 * @param[in] count How many philo threads to kill
 * @param[in] monitor If monitor thread should be killed
 */
void	destroy_threads(t_info *info, size_t count, bool monitor)
{
	size_t	idx;

	idx = 0;
	if (monitor)
		pthread_join(info->monitor, NULL);
	if (count == 1)
	{
		pthread_detach(info->philos[idx].thread);
		return ;
	}
	while (idx < count)
	{
		pthread_join(info->philos[idx].thread, NULL);
		idx++;
	}
}
