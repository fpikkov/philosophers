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

static size_t	philo_atoi(const char *str)
{
	size_t	nbr;

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

static bool	init_philo(t_info *info, size_t idx, int argc, char **argv)
{
	info->philos[idx].id = idx;
	info->philos[idx].death_time = philo_atoi(argv[2]);
	info->philos[idx].eat_time = philo_atoi(argv[3]);
	info->philos[idx].sleep_time = philo_atoi(argv[4]);
	if (info->philos[idx].death_time < 1 || info->philos[idx].eat_time < 1 \
	|| info->philos[idx].sleep_time < 1)
		return (false);
	if (argc == 6)
	{
		info->philos[idx].eat_amount = (int32_t)philo_atoi(argv[5]);
		if (info->philos[idx].eat_amount < 1)
			return (false);
	}
	else
		info->philos[idx].eat_amount = -1;
	return (true);
}

static bool	create_philos(t_info *info, int argc, char **argv)
{
	size_t	idx;

	idx = 0;
	info->philos = (t_philo *)malloc(info->count * sizeof(t_philo));
	if (!info->philos)
		return (false);
	memset(info->philos, 0, info->count * sizeof(t_philo));
	while (idx < info->count)
	{
		if (!init_philo(info, idx, argc, argv))
			return (false);
		idx++;
	}
	return (true);
}

static bool	parse_info(t_info *info, int argc, char **argv)
{
	if (argc < 5)
		return (false);
	info->halt = false;
	info->count = philo_atoi(argv[1]);
	if (info->count < 1)
		return (false);
	info->forks = (pthread_mutex_t *)malloc \
	(sizeof(pthread_mutex_t) * info->count);
	if (!info->forks)
		return (false);
	return (true);
}

/**
 * @brief Parses the given arguments and stores the values in a struct.
 * Also attempts to build all the philosopher structs.
 * @param[in] argc Aargument counter from main()
 * @param[in] argv Argument vector from main()
 * @return Pointer to t_info type struct on success, otherwise NULL
 */
t_info	*parse_args(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	if (!parse_info(info, argc, argv))
		return (free(info), NULL);
	if (!create_philos(info, argc, argv))
		return (free_info(info), NULL);
	set_addresses(info);
	return (info);
}
