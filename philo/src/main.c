#include "philo.h"

/**
 * *** PSEUDOCODE ***
 *
 * 1. Parse args so you can get the integers for each arg.
 *     Consider argc[6] exit conditions if it exists.
 * 2. Create threads for each philospher. (Do philos get their own structs/ LL?)
 * 3. Create equal amount of forks through mutex.
 * 4. Run sim: eat > sleep > think > eat
 * 5. (a) Uneven no. philos will grab a fork to their left AND THEN the right.
 *         Evem no. philos will do so in opposite order. Asymmetry prevents deadlock.
 *    (b) Alternatively implement a multithreading solution to avoid deadlock.
 * 6. Exit program and free resources once a philo dies or they have eaten enough.
 */

static int	print_error(t_error err)
{
	if (err == MISSING_ARGS)
		(void)write(STDERR_FILENO, "Incorrect number of args.\n", 27);
	else if (err == PARSE_FAILURE)
		(void)write(STDERR_FILENO, "Error in parsing values\n", 25);
	else if (err == THREAD_FAILURE)
		(void)write(STDERR_FILENO, "Failed to allocate threads.\n", 29);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_info		*info;

	if (argc < 5 || argc > 6)
		return (print_error(MISSING_ARGS));
	info = parse_args(argc, argv);
	if (!info)
		return (print_error(PARSE_FAILURE));
	if (!alloc_threads(info))
		return (print_error(THREAD_FAILURE));
	// Rest of the code

	if (info)
		free(info);
	return (EXIT_SUCCESS);
}
