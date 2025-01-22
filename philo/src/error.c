/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:52:23 by fpikkov           #+#    #+#             */
/*   Updated: 2025/01/22 13:52:25 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*error_text(t_error error)
{
	const char	*names[4]
		= {
		"Usage: philo [num_philos] [time_to_die] [time_to_eat] \
[time_to_sleep] [optional: amount_to_eat]",
		"Parsing error: Did you try entering positive integers?",
		"Thread error: issue creating threads",
		"Generic error"
	};

	if (error >= 10 && error <= 13)
		return (names[error - 10]);
	return (names[3]);
}

int	print_error(t_error error)
{
	printf("%s\n", error_text(error));
	return (EXIT_FAILURE);
}
