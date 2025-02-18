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

static void	eat_pasta(t_philo *philo, t_mutex *first, t_mutex *second)
{
	pthread_mutex_lock(first);
	log_event(philo, FORK);
	pthread_mutex_lock(second);
	log_event(philo, FORK);
	pthread_mutex_lock(philo->meal);
	philo->timer_last_meal = time_in_ms(philo->start_time);
	if (philo->eat_amount > 0)
		philo->eat_amount--;
	pthread_mutex_unlock(philo->meal);
	log_event(philo, EATING);
	sleep_for_ms(philo->start_time, philo->eat_time, philo->halt);
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
	if (philo->eat_amount == 0)
		return (false);
	eat_pasta(philo, philo->left_fork, philo->right_fork);
	if (*philo->halt == true)
		return (true);
	log_event(philo, SLEEPING);
	sleep_for_ms(philo->start_time, philo->sleep_time, philo->halt);
	if (*philo->halt == true)
		return (true);
	log_event(philo, THINKING);
	sleep_for_ms(philo->start_time, philo->think_time, philo->halt);
	if (*philo->halt == true)
		return (true);
	return (false);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!(*philo->start))
		continue ;
	if (philo->id % 2)
	{
		if (philo->think_time != 0)
			sleep_for_ms(philo->start_time, (philo->think_time / 2), philo->halt);
		else
			usleep(500);
	}
	pthread_mutex_lock(philo->meal);
	philo->timer_last_meal = time_in_ms(philo->start_time);
	pthread_mutex_unlock(philo->meal);
	while (true)
	{
		if (philo_life(philo))
			break ;
	}
	return (NULL);
}
