/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:05:39 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 17:05:40 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * TODO: Detach threads and mutexes
 */
void	free_info(t_info *info)
{
	if (!info)
		return ;
	if (info->philos)
	{
		free(info->philos);
		info->philos = NULL;
	}
	if (info->forks)
	{
		free(info->forks);
		info->forks = NULL;
	}
	free(info);
	info = NULL;
}
