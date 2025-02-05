/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:36:13 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 17:36:14 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>

// Enumeration for destroying specific mutexes
typedef enum e_flags
{
	FORKS = 1 << 0,
	DEAD = 1 << 1,
	PRINT = 1 << 2,
	ALL = FORKS | DEAD | PRINT
}	t_flags;

// Enumeration for picking the correct error message.
typedef enum e_error
{
	MISSING_ARGS = 10,
	PARSE_FAILURE,
	THREAD_FAILURE,
	ERR_GENERIC
}	t_error;

// Enumeration for the philosopher states.
typedef enum e_state
{
	THINKING = 0,
	EATING,
	SLEEPING
}	t_state;

/**
 * @brief Struct which stores data for each philosopher.
 * @param halt whether the simulation should stop
 * @param thread the thread associated with the philosopher
 * @param id the id of the philosopher
 * @param death_time the time it takes for a philo to die
 * @param eat_time the time it takes for a philo to eat
 * @param sleep_time the time it takes for a philo to sleep
 * @param eat_amount optional, the times each philo has to eat
 * @param timer_last_meal time elapsed since last meal
 */
typedef struct s_philo
{
	bool			*halt;
	pthread_t		thread;
	int32_t			id;
	int32_t			death_time;
	int32_t			eat_time;
	int32_t			sleep_time;
	int32_t			eat_amount;
	pthread_mutex_t	*halt_sim;
	pthread_mutex_t	*printing;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct timeval	timer_last_meal;
}					t_philo;

/**
 * @brief Struct for storing variables from the argment vector.
 * @param halt halts the simulation
 * @param monitor the monitor thread which tracks the conditions of philos
 * @param count the amount of philosophers
 * @param philos the structs storing each philosopher
 * @param forks the array containing all forks
 * @param halt_sim mutex for stopping simulation
 * @param printing if writing log messages, locks the mutex
 */
typedef struct s_info
{
	bool			halt;
	pthread_t		monitor;
	int32_t			count;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	halt_sim;
	pthread_mutex_t	printing;
}					t_info;

// --- Setup functions ---

t_info	*parse_args(int argc, char **argv);
void	set_addresses(t_info *info);
bool	init_mutexes(t_info *info);

// --- Routine functions ---

void	monitor_routine(void *arg);
void	philo_routine(void *arg);

// --- Logging functions ---

int		print_error(t_error error);
void	log_death(t_info *info, int32_t num);
void	log_event(t_philo *philo, t_state state);

// --- Cleanup functions ---

void	free_info(t_info *info);
void	destroy_mutexes(t_info *info, int32_t count, t_flags flag);
void	destroy_threads(t_info *info, int32_t count, bool monitor);

#endif
