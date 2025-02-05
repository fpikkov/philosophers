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

static void	grab_forks(bool **stop, pthread_mutex_t **lf, pthread_mutex_t **rf)
{
	while (!(*stop))
	{
		while (pthread_mutex_lock(*lf))
			usleep(5);
		printf("Left locked\n");
		if (pthread_mutex_lock(*rf))
		{
			pthread_mutex_unlock(*lf);
			continue ;
		}
		printf("Right locked\n");
		break ;
	}
}

static void	start_eating(t_philo *philo)
{
	if (philo->eat_amount == 0)
		return ;
	if (philo->id % 2)
	{
		grab_forks(&philo->halt, &philo->right_fork, &philo->left_fork);
		log_event(philo, EATING);
		sleep_for_ms(philo->eat_time);
		philo->timer_last_meal = time_in_ms();
		if (philo->eat_amount > 0)
			philo->eat_amount--;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		grab_forks(&philo->halt, &philo->left_fork, &philo->right_fork);
		log_event(philo, EATING);
		sleep_for_ms(philo->eat_time);
		philo->timer_last_meal = time_in_ms();
		if (philo->eat_amount > 0)
			philo->eat_amount--;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
