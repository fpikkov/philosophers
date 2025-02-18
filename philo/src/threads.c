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

static void	assign_forks(t_info *info, size_t idx)
{
	if (idx % 2)
	{
		info->philos[idx].right_fork = &info->forks[idx % info->count];
		info->philos[idx].left_fork = &info->forks[(idx + 1) % info->count];
	}
	else
	{
		info->philos[idx].left_fork = &info->forks[idx % info->count];
		info->philos[idx].right_fork = &info->forks[(idx + 1) % info->count];
	}
}

/**
 * @brief Sets the pointers in t_philo to the adressses in t_info.
 * Right fork is found with the formula: index % N.
 * Left fork is found with the formula: index + 1 % N.
 * @param info Master structure of the project
 */
void	set_addresses(t_info *info)
{
	size_t	idx;
	size_t	count;

	if (!info || !info->philos)
		return ;
	idx = 0;
	count = info->count;
	while (idx < count)
	{
		assign_forks(info, idx);
		info->philos[idx].halt_sim = &info->halt_sim;
		info->philos[idx].printing = &info->printing;
		info->philos[idx].meal = &info->meals[idx];
		info->philos[idx].halt = &info->halt;
		info->philos[idx].start = &info->start;
		idx++;
	}
}

static bool	init_meals(t_info *info)
{
	size_t	idx;

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
	size_t	idx;

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
