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
	const char	*names[8]
		= {
		"Usage: philo [num_philos] [time_to_die] [time_to_eat] \
[time_to_sleep] [optional: amount_to_eat]",
		"Thread error: issue creating threads",
		"Parsing error: time was less than 60ms",
		"Parsing error: incorrect amount of philosophers",
		"System error: malloc failed",
		"Parsing error: incorrect amount of meals to eat",
		"System error: unable to initialize mutexes",
		"Generic error"
	};

	if (error >= 10 && error <= 17)
		return (names[error - 10]);
	return (names[7]);
}

/**
 * @brief Prints an error message based on an enum
 * @param[in] error a value from the t_error enum
 * @param[in] escape return value override
 * @return EXIT_FAILURE in all cases
 */
int	print_error(t_error error, bool escape)
{
	printf("%s\n", error_text(error));
	if (!escape)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
