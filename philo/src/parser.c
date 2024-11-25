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

t_info	*parse_args(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->count = philo_atoi(argv[1]);
	info->death_time = philo_atoi(argv[2]);
	info->eat_time = philo_atoi(argv[3]);
	info->sleep_time = philo_atoi(argv[4]);
	if (info->count < 1 || info->death_time < 1
		|| info->eat_time < 1 || info->sleep_time < 1)
		return (free(info), NULL);
	if (argc == 6)
	{
		info->eat_amount = philo_atoi(argv[5]);
		if (info->eat_amount < 1)
			return (free(info), NULL);
	}
	else
		info->eat_amount = 0; // Change to -1 if used as counter
	info->philos = NULL;
	info->forks = NULL;
	return (info);
}
