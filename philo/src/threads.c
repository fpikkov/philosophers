/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:52:51 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 13:52:52 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_addresses(t_info *info)
{
	int32_t	idx;
	int32_t	count;

	if (!info || !info->philos)
		return ;
	idx = 0;
	count = info->count;
	while (idx < count)
	{
		info->philos[idx].right_fork = &info->forks[(idx + count - 1) % count];
		info->philos[idx].left_fork = &info->forks[(idx + 1) % count];
		info->philos[idx].philos_fed = &info->philos_fed;
		info->philos[idx].philo_died = &info->philo_died;
		info->philos[idx].printing = &info->printing;
		idx++;
	}
}
