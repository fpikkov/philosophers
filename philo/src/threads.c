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

/**
 * *** PSEUDOCODE ***
 *
 * The potentially better way is to give each philo their own struct.
 * This will enable each one to have their own timers and eat counter.
 *
 * But then where to store each mutex fork?
 */
bool	alloc_threads(t_info *info)
{
	int32_t	idx;
	int32_t	count;

	if (!info)
		return (false);
	idx = 0;
	count = info->count;
	while (idx < count)
	{

		idx++;
	}
	return (true);
}
