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
 * @param dead has the philosopher died
 * @param thread the thread associated with the philosopher
 * @param id the id of the philosopher connected with the struct
 * @param state the current state of the philosopher
 * @param death_time the time it takes for a philo to die
 * @param eat_time the time it takes for a philo to eat
 * @param sleep_time the time it takes for a philo to sleep
 * @param eat_amount optional, the times each philo has to eat
 * @param timer the time elapsed since the last state change
 * @param timer_last_meal time elapsed since last meal
 */
typedef struct s_philo
{
	bool		dead;
	pthread_t	thread;
	int32_t		id;
	t_state		state;
	int32_t		death_time;
	int32_t		eat_time;
	int32_t		sleep_time;
	int32_t		eat_amount;
	int32_t		timer;
	int32_t		timer_last_meal;
}				t_philo;

/**
 * @brief Struct for storing variables from the argment vector.
 * @param halt halts the simulation
 * @param monitor the monitor thread which tracks the conditions of philos
 * @param count the amount of philosophers
 * @param philos the structs storing each philosopher
 * @param forks the array containing all forks
 * @param dead_mutex if a philo dies, locks the mutex
 * @param print_mutex if writing log messages, locks the mutex
 * @param philos_fed locks the mutex if all philos are fed
 */
typedef struct s_info
{
	bool			halt;
	pthread_t		monitor;
	int32_t			count;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	philos_fed;
}					t_info;

/**
 * Parses the given arguments and stores the values in an allocated struct.
 * @param[in] argc Argument counter from main()
 * @param[in] argv Argument vector from main()
 * @return Pointer to t_info type struct on success, otherwise NULL
 */
t_info	*parse_args(int argc, char **argv);
/**
 * Allocates threads on the heap for philosophers and mutex threads for forks.
 * @param[in] info The pre-allocated type t_info where to store threads
 * @param[out] info On success allocated params philos and forks
 * @return true on successful allocation, otherwise false
 */
bool	alloc_threads(t_info *info);

// Error logging

int		print_error(t_error error);

// Cleanup functions

void	free_info(t_info *info);

/**
 * *** ALLOWED FUNCTIONS ***
 *
 * LIBFT AUTHORIZED : NO
 *
 * string.h		: memset
 * stdio.h		: printf
 * stdlib.h		: malloc, free
 * unistd.h		: write, usleep
 * sys/time.h	: gettimeofday
 * pthread.h	:
 * 	pthread_	- create, detach, join
 * 		mutex_	- init, destroy, lock, unlock
 */

/**
 * *** GLOBAL RULES ***
 *
 * 1. Global variables are forbidden!
 * 2. Args: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep,
 *          [number_of_times_each_philosopher_must_eat]
 * - The number of philosophers and also the number of forks.
 * - If a philo didn't start eating "time_to_die" ms since their last meal
 *    or the beginning of simulation they die.
 * - The time it takes for a philosopher to eat while holding two forks.
 * - The time a philosopher will spend sleeping (in milliseconds).
 * - (optional) Simulation stops when each philo has eaten specified times.
 *   Otherwise simulation will end when a philo dies.
 * 3. Each philosopher has a number ranging from 1 to number_of_philosophers.
 * 4. Philo [1] sits next to philo [number_of_philosophers].
 *    Other philos [N] sits between philo [N - 1] and philo [N + 1].
 * 5. Your program must not have any data races.
 */

/**
 * *** PROGRAM LOGS ***
 *
 * 1.  Any state change of a philosopher must be formatted as follows :
 * 		- timestamp_in_ms X has taken a fork
 * 		- timestamp_in_ms X is eating
 * 		- timestamp_in_ms X is sleeping
 * 		- timestamp_in_ms X is thinking
 * 		- timestamp_in_ms X died
 * 2. A displayed state message should not be mixed up with another message.
 * 3. Philosopher death should be displayed within 10 ms after the event.
 */

/**
 * *** OVERVIEW ***
 *
 * 1. One or more philosophers sit at a round table.
 *    There is a large bowl of spaghetti in the middle of the table.
 * 2. The philosophers alternatively eat, think, or sleep.
 * 3. There are as many forks as philosophers.
 * 4. A philosopher takes their right and their left forks to eat.
 * 5. Philosopher's cycle: finish eating (return forks) > sleep > think.
 *    The simulation stops when a philosopher dies of starvation.
 * 6. Every philosopher needs to eat and should never starve.
 * 7. Philosophers don’t speak with each other.
 * 8. Philosophers don’t know if another philosopher is about to die.
 * 9. Philosophers should avoid dying.
 */

/**
 * *** GUIDELINES ***
 *
 * 1. Each philosopher should be a thread.
 * 2. There is one fork between each pair of philosophers.
 *    For only one philosopher, there should be only one fork on the table.
 * 3. To prevent philosophers from duplicating forks,
 *    you should protect the forks state with a mutex for each of them.
 */

#endif
