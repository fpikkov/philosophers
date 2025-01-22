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

static int	philo_atoi(const char *str)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (*str >= '0' && *str <= '9' && (!(nbr > INT_MAX) || !(nbr < INT_MIN)))
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (sign == -1 && !(nbr > 2147483648L))
		nbr *= sign;
	if (nbr > INT_MAX || nbr < INT_MIN || *str != '\0')
		return (0);
	return ((int)nbr);
}

static bool	parse_info(t_info *info, int argc, char **argv)
{
	info->dead = false;
	info->count = philo_atoi(argv[1]);
	if (info->count < 1)
		return (false);
	return (true);
}

static bool	init_philo(t_info *info, int32_t idx, int argc, char **argv)
{
	info->philos[idx].death_time = philo_atoi(argv[2]);
	info->philos[idx].eat_time = philo_atoi(argv[3]);
	info->philos[idx].sleep_time = philo_atoi(argv[4]);
	if (info->philos[idx].death_time < 1 || info->philos[idx].eat_time < 1
		|| info->philos[idx].sleep_time < 1)
		return (false);
	if (argc == 6)
	{
		info->philos[idx].eat_amount = philo_atoi(argv[5]);
		if (info->philos[idx].eat_amount < 1)
			return (false);
	}
	else
		info->philos[idx].eat_amount = -1;
	return (true);
}

static bool	create_philos(t_info *info, int argc, char **argv)
{
	int32_t	idx;

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
	return (info);
}
