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
	if (info->meals)
	{
		free(info->meals);
		info->meals = NULL;
	}
}

/**
 * @brief Destroys mutexes based on flags and up to but not including count
 * @param[in] info Master structure of the project
 * @param[in] count How many mutexes to destroy
 * @param[in] flag Which mutex types to destroy
 */
void	destroy_mutexes(t_info *info, int64_t count, t_flags flag)
{
	int64_t	idx;

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
	idx = 0;
	while (idx < count && (flag & MEAL))
	{
		pthread_mutex_destroy(&info->meals[idx]);
		idx++;
	}
}

/**
 * @brief Destroys all threads by using pthread_join
 * @param[in] info Master struct of the project
 * @param[in] count How many philo threads to kill
 */
void	destroy_threads(t_info *info, int64_t count)
{
	int64_t	idx;

	idx = 0;
	while (idx < count)
	{
		pthread_join(info->philos[idx].thread, NULL);
		idx++;
	}
}

void	log_event(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->printing);
	if (state == DEATH)
		printf("%ld %ld died\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == THINKING && !(*philo->halt))
		printf("%ld %ld is thinking\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == EATING && !(*philo->halt))
		printf("%ld %ld is eating\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == SLEEPING && !(*philo->halt))
		printf("%ld %ld is sleeping\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	else if (state == FORK && !(*philo->halt))
		printf("%ld %ld has taken a fork\n", \
		time_in_ms() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(philo->printing);
}
