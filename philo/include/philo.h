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

// Hard cap on amount of philosophers
# define P_LIMIT 500

// Enumeration for destroying specific mutexes
typedef enum e_flags
{
	FORKS = 1 << 0,
	DEAD = 1 << 1,
	PRINT = 1 << 2,
	MEAL = 1 << 3,
	ALL = FORKS | DEAD | PRINT | MEAL
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
	SLEEPING,
	FORK
}	t_state;

// Ease of use type definition
typedef pthread_mutex_t	t_mutex;

/**
 * @brief Struct which stores data for each philosopher.
 * @param start when the simulation should begin
 * @param halt whether the simulation should stop
 * @param thread the thread associated with the philosopher
 * @param id the id of the philosopher
 * @param death_time the time it takes for a philo to die
 * @param eat_time the time it takes for a philo to eat
 * @param sleep_time the time it takes for a philo to sleep
 * @param think_time the time it takes for a philo to think
 * @param eat_amount optional, the times each philo has to eat
 * @param timer_last_meal timestamp of previous meal
 */
typedef struct s_philo
{
	_Atomic bool	*start;
	_Atomic bool	*halt;
	pthread_t		thread;
	size_t			id;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			think_time;
	size_t			start_time;
	int32_t			eat_amount;
	t_mutex			*halt_sim;
	t_mutex			*printing;
	t_mutex			*meal;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	size_t			timer_last_meal;
}					t_philo;

/**
 * @brief Struct for storing variables from the argment vector.
 * @param start synchronizes all threads
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
	_Atomic bool	start;
	_Atomic bool	halt;
	bool			should_eat;
	size_t			count;
	size_t			meal_mutexes;
	size_t			start_time;
	t_philo			*philos;
	t_mutex			*forks;
	t_mutex			halt_sim;
	t_mutex			printing;
	t_mutex			*meals;
}					t_info;

// --- Setup functions ---

t_info	*parse_args(int argc, char **argv);
void	set_addresses(t_info *info);
bool	init_mutexes(t_info *info);

// --- Routine functions ---

void	monitor_routine(t_info *info);
void	*philo_routine(void *arg);
bool	start_routines(t_info *info);

// --- Logging functions ---

int		print_error(t_error error);
void	log_death(t_info *info, size_t num);
void	log_event(t_philo *philo, t_state state);
size_t	time_in_ms(size_t start);
void	sleep_for_ms(size_t begin, size_t msec);

// --- Cleanup functions ---

void	free_info(t_info *info);
void	destroy_mutexes(t_info *info, size_t count, t_flags flag);
void	destroy_threads(t_info *info, size_t count);

#endif
