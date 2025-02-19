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

# ifndef DEBUG
#  define DEBUG 0
# endif

// Hard limits on parameters
# define P_LIMIT 400
# define TIME_MIN 60

// Fine-tuning of timings
# define START_MULTIPLIER 6
# define TIME_DIVISOR 2
# define MONITOR_COOLDOWN 1000
# define BEGIN_SLEEP 50
# define SLEEP_USEC 100
# define THINK_LIMIT 600
# define THINK_CLAMP 200

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
	THREAD_FAILURE,
	PARSE_TIME,
	PARSE_PHILO,
	MALLOC_FAILURE,
	PARSE_MEALS,
	MUTEX_FAILURE,
	ERR_GENERIC
}	t_error;

// Enumeration for the philosopher states.
typedef enum e_state
{
	THINKING = 0,
	EATING,
	SLEEPING,
	FORK,
	DEATH
}	t_state;

// Ease of use type definition
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef struct s_info	t_info;

/**
 * @brief Struct which stores data for each philosopher.
 * @param start when the simulation should begin
 * @param halt whether the simulation should stop
 * @param thread the thread associated with the philosopher
 * @param id the id of the philosopher
 * @param think_time the time it takes for a philo to think
 * @param eat_amount optional, the times each philo has to eat
 * @param last_meal timestamp of previous meal
 */
typedef struct s_philo
{
	_Atomic bool	*halt;
	t_info			*info;
	pthread_t		thread;
	int64_t			id;
	int64_t			last_meal;
	int64_t			think_time;
	int64_t			eat_amount;
	t_mutex			*halt_sim;
	t_mutex			*printing;
	t_mutex			*meal;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
}					t_philo;

/**
 * @brief Struct for storing variables from the argment vector.
 * @param start synchronizes all threads
 * @param halt halts the simulation
 * @param monitor the monitor thread which tracks the conditions of philos
 * @param death_time the time it takes for a philo to die
 * @param eat_time the time it takes for a philo to eat
 * @param sleep_time the time it takes for a philo to sleep
 * @param count the amount of philosophers
 * @param philos the structs storing each philosopher
 * @param forks the array containing all forks
 * @param halt_sim mutex for stopping simulation
 * @param printing if writing log messages, locks the mutex
 */
typedef struct s_info
{
	_Atomic bool	halt;
	bool			should_eat;
	int64_t			count;
	int64_t			start_time;
	int64_t			death_time;
	int64_t			eat_time;
	int64_t			sleep_time;
	int64_t			eat_amount;
	t_philo			*philos;
	t_mutex			*forks;
	t_mutex			halt_sim;
	t_mutex			printing;
	t_mutex			*meals;
}					t_info;

// --- Setup functions ---

t_info	*parse_args(int argc, char **argv);

// --- Routine functions ---

void	monitor_routine(t_info *info);
void	*philo_routine(void *arg);
void	*philo_single(void *arg);
bool	start_routines(t_info *info);

// --- Mutex functions ---

bool	init_mutexes(t_info *info);

// --- Logging functions ---

int		print_error(t_error error, bool escape);
void	log_event(t_philo *philo, t_state state);
int64_t	time_in_ms(void);
void	sleep_for_ms(int64_t msec, _Atomic bool *halt);

// --- Cleanup functions ---

void	free_info(t_info *info);
void	destroy_mutexes(t_info *info, int64_t count, t_flags flag);
void	destroy_threads(t_info *info, int64_t count);

/*
	!!!! TIME TO THINK !!!!

	info->philos[idx].id = idx;
	if ((info->philos[idx].eat_time + info->philos[idx].sleep_time) \
	< info->philos[idx].death_time)
		info->philos[idx].think_time = (info->philos[idx].death_time \
		- (info->philos[idx].eat_time + info->philos[idx].sleep_time)) / 4;

*/

#endif
