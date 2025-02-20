/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:52:42 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 13:52:44 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int64_t	philo_atoi(const char *str)
{
	int64_t	nbr;

	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			return (0);
	while (*str >= '0' && *str <= '9' && !(nbr > INT_MAX))
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX || *str != '\0')
		return (0);
	return (nbr);
}

static bool	parse_info(t_info *info, int argc, char **argv)
{
	info->count = philo_atoi(argv[1]);
	info->death_time = philo_atoi(argv[2]);
	info->eat_time = philo_atoi(argv[3]);
	info->sleep_time = philo_atoi(argv[4]);
	if (info->count < 1 || info->count > P_LIMIT)
		return (print_error(PARSE_PHILO, false));
	if (info->death_time < TIME_MIN || info->eat_time < TIME_MIN \
	|| info->sleep_time < TIME_MIN)
		return (print_error(PARSE_TIME, false));
	info->eat_amount = -1;
	if (argc == 6)
	{
		info->eat_amount = philo_atoi(argv[5]);
		if (info->eat_amount < 1)
			return (print_error(PARSE_MEALS, false));
	}
	info->forks = (t_mutex *)malloc(sizeof(t_mutex) * info->count);
	if (!info->forks)
		return (print_error(MALLOC_FAILURE, false));
	info->meals = (t_mutex *)malloc(sizeof(t_mutex) * info->count);
	if (!info->meals)
		return (print_error(MALLOC_FAILURE, false));
	return (true);
}

static void	assign_forks(t_info *info, int64_t idx)
{
	if (idx % 2)
	{
		info->philos[idx].right_fork = &info->forks[idx];
		info->philos[idx].left_fork = &info->forks[(idx + 1) % info->count];
	}
	else
	{
		info->philos[idx].left_fork = &info->forks[idx];
		info->philos[idx].right_fork = &info->forks[(idx + 1) % info->count];
	}
}

/**
 * @brief Sets the pointers in t_philo to the adressses in t_info.
 * Right fork is found with the formula: index % N.
 * Left fork is found with the formula: index + 1 % N.
 * @param info Master structure of the project
 */
static void	set_addresses(t_info *info)
{
	int64_t	idx;
	int64_t	count;

	if (!info || !info->philos)
		return ;
	idx = 0;
	count = info->count;
	while (idx < count)
	{
		info->philos[idx].id = idx;
		assign_forks(info, idx);
		info->philos[idx].info = info;
		info->philos[idx].halt_sim = &info->halt_sim;
		info->philos[idx].printing = &info->printing;
		info->philos[idx].meal = &info->meals[idx];
		info->philos[idx].halt = &info->halt;
		info->philos[idx].eat_amount = info->eat_amount;
		idx++;
	}
}

/**
 * @brief Parses the given arguments and stores the values in a struct.
 * Also attempts to build all the philosopher structs.
 * @param[in] info The main structure of the program
 * @param[in] argc Argument counter from main()
 * @param[in] argv Argument vector from main()
 * @return true if parsing was successful, otherwise false
 */
bool	parse_args(t_info *info, int argc, char **argv)
{
	memset(info, 0, sizeof(t_info));
	if (!parse_info(info, argc, argv))
		return (free_info(info), false);
	info->philos = (t_philo *)malloc(info->count * sizeof(t_philo));
	if (!info->philos)
	{
		print_error(MALLOC_FAILURE, false);
		return (free_info(info), false);
	}
	memset(info->philos, 0, info->count * sizeof(t_philo));
	if (info->eat_amount > 0)
		info->should_eat = true;
	set_addresses(info);
	if (!init_mutexes(info))
	{
		print_error(MUTEX_FAILURE, false);
		return (free_info(info), false);
	}
	return (true);
}
