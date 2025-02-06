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
	log_event(philo, EATING);
	sleep_for_ms(philo->eat_time);
	philo->timer_last_meal = time_in_ms();
	if (philo->eat_amount > 0)
		philo->eat_amount--;
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

static void	start_eating(t_philo *philo)
{
	if (philo->eat_amount == 0)
		return ;
	if (philo->id % 2)
		eat_pasta(philo, philo->right_fork, philo->left_fork);
	else
	{
		usleep(5);
		eat_pasta(philo, philo->left_fork, philo->right_fork);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!(*philo->start))
		continue ;
	philo->timer_last_meal = time_in_ms();
	while (!(*philo->halt))
	{
		log_event(philo, THINKING);
		start_eating(philo);
		log_event(philo, SLEEPING);
		sleep_for_ms(philo->sleep_time);
	}
	return (NULL);
}
