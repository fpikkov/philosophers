/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:43:34 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/03 12:43:36 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_routines(t_info *info)
{
	int32_t	idx;

	idx = 0;
	if (!info)
		return (false);
	if (pthread_create(&info->monitor, NULL,
			monitor_routine, (void*)info) != 0)
		return (false);
	while (idx < info->count)
	{
		if (pthread_create(&info->philos[idx].thread, NULL, \
		philo_routine, (void *)(&info->philos[idx])) != 0)
		{
			destroy_threads(info, idx, true);
			return (false);
		}
	}
	return (true);
}
