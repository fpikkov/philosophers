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

static bool	has_philo_died(t_info *info, int32_t idx)
{
	struct timeval	tv;
	int32_t			current;

	gettimeofday(&tv, NULL);
	current = tv.tv_usec - info->philos[idx].timer_last_meal.tv_usec;
	if (current >= info->philos[idx].death_time
			&& (info->philos[idx].eat_amount > 0
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
	int32_t	idx;

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

static void	monitor_routine(void *arg)
{
	t_info	*info;
	int32_t	idx;

	info = (t_info *)arg;
	while (!info->halt)
	{
		idx = 0;
		while (idx < info->count)
		{
			if (has_philo_died(info, idx))
			{
				log_death(info, idx);
				break ;
			}
			idx++;
		}
		if (have_philos_eaten(info))
			break ;
	}
}

static void	grab_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
	while (true)
	{
		while (pthread_mutex_lock(left))
			usleep(5);
		if (pthread_mutex_lock(right))
		{
			pthread_mutex_unlock(left);
			continue ;
		}
		break ;
	}
}
static bool start_eating(t_philo *philo)
{
	if (philo->id % 2)
	{
		grab_forks(philo->right_fork, philo->left_fork);
		log_event(philo, EATING);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		grab_forks(philo->left_fork, philo->right_fork);
		log_event(philo, EATING);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
static void	philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	gettimeofday(&philo->death_time, NULL);
	while (!philo->halt)
	{
		// TODO: Philo subroutine
		// TODO: Call start_eating
		// TODO: Put the reest of mutex locks inside of while loops
	}
}

bool	start_routines(t_info *info)
{
	int32_t	idx;

	idx = 0;
	if (!info)
		return (false);
	if (pthread_create(&info->monitor, NULL,
			monitor_routine, (void*)info) != 0)
		return (false);
	while (idx < info->count)
	{
		if (pthread_create(&info->philos[idx].thread, NULL,
				philo_routine, (void*)(&info->philos[idx])) != 0)
		{
			destroy_threads(info, idx, true);
			return (false);
		}
	}
	return (true);
}
