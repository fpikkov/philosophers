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
	philo->timer_last_meal = time_in_ms();
	if (philo->eat_amount > 0)
		philo->eat_amount--;
	pthread_mutex_unlock(philo->meal);
	log_event(philo, EATING);
	sleep_for_ms(philo->eat_time);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

static void	start_eating(t_philo *philo)
{
	if (philo->eat_amount == 0)
		return ;
	if (philo->id % 2)
		eat_pasta(philo, philo->right_fork, philo->left_fork);
	else
		eat_pasta(philo, philo->left_fork, philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!(*philo->start))
		continue ;
	if (philo->id % 2)
		usleep(500);
	philo->timer_last_meal = time_in_ms();
	while (!(*philo->halt))
	{
		start_eating(philo);
		if (*philo->halt)
			return (NULL);
		log_event(philo, SLEEPING);
		sleep_for_ms(philo->sleep_time);
		log_event(philo, THINKING);
		sleep_for_ms(philo->think_time);
	}
	return (NULL);
}
