/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:51:33 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/05 11:51:35 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think_time(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	philo->think_time = (philo->info->death_time \
	- (time_in_ms() - philo->last_meal) - philo->info->eat_time) / TIME_DIVISOR;
	if (philo->think_time < 0)
		philo->think_time = 0;
	else if (philo->think_time > THINK_LIMIT)
		philo->think_time = THINK_CLAMP;
	pthread_mutex_unlock(philo->meal);
}

static void	eat_pasta(t_philo *philo, t_mutex *first, t_mutex *second)
{
	pthread_mutex_lock(first);
	log_event(philo, FORK);
	pthread_mutex_lock(second);
	log_event(philo, FORK);
	pthread_mutex_lock(philo->meal);
	philo->last_meal = time_in_ms();
	if (philo->eat_amount > 0)
		philo->eat_amount--;
	pthread_mutex_unlock(philo->meal);
	log_event(philo, EATING);
	sleep_for_ms(philo->info->eat_time, philo->halt);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

/**
 * @return true if the thread should end, otherwise false
 */
static bool	philo_life(t_philo *philo)
{
	if (*philo->halt == true)
		return (true);
	pthread_mutex_lock(philo->meal);
	if (philo->eat_amount == 0)
	{
		pthread_mutex_unlock(philo->meal);
		return (false);
	}
	pthread_mutex_unlock(philo->meal);
	eat_pasta(philo, philo->left_fork, philo->right_fork);
	if (*philo->halt == true)
		return (true);
	log_event(philo, SLEEPING);
	sleep_for_ms(philo->info->sleep_time, philo->halt);
	if (*philo->halt == true)
		return (true);
	log_event(philo, THINKING);
	if (philo->info->count % 2 != 0)
	{
		think_time(philo);
		sleep_for_ms(philo->think_time, philo->halt);
	}
	return (false);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->meal);
	philo->last_meal = philo->info->start_time;
	pthread_mutex_unlock(philo->meal);
	while (time_in_ms() < philo->last_meal)
		continue ;
	if (philo->id % 2)
	{
		think_time(philo);
		if (philo->think_time != 0)
			sleep_for_ms(philo->think_time, philo->halt);
		else
			usleep(BEGIN_SLEEP);
	}
	while (true)
	{
		if (philo_life(philo))
			break ;
	}
	return (NULL);
}

void	*philo_single(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->meal);
	philo->last_meal = philo->info->start_time;
	pthread_mutex_unlock(philo->meal);
	while (time_in_ms() < philo->last_meal)
		continue ;
	pthread_mutex_lock(philo->left_fork);
	log_event(philo, FORK);
	pthread_mutex_unlock(philo->left_fork);
	while (*philo->halt == false)
		usleep(100);
	return (NULL);
}
