#include "philo.h"

/* pthread_t	*spawn(int32_t amount)
{
	pthread_t	*philos;
	int32_t		i;

	if (amount < 1)
		return (NULL);
	philos = (pthread_t *)malloc(sizeof(pthread_t) * amount);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < amount)
	{

	}
	return (philos);
} */

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
	uint32_t	count;

	if (!info)
		return (false);
	count = info->count;
	info->philos = (pthread_t *)malloc(sizeof(pthread_t) * count);
	if (!info->philos)
		return (false);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	if (!info->forks)
	{
		if (info->philos)
			free(info->philos);
		free(info);
		return (false);
	}
	return (true);
}
