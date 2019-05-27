/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** main file
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "philosopher.h"

int	display_usage(void)
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\n");
	printf("DESCRIPTION\n\t-p nbr_p\tnumber of philosophers\n");
	printf("\t-e nbr_e\tmaximum number times a philosopher eats");
	printf(" before exiting the program");
	return (0);
}

int	main(int ac, char **av)
{
	RCFStartup(ac, av);
	if (ac == 2 && strcmp(av[1], "--help") == 0)
		return (display_usage());
	else if (ac != 5) {
		dprintf(2, "Invalid number of argument\n");
		return (84);
	}
	else if (strcmp(av[1], "-p") != 0 || strcmp(av[3], "-e") != 0) {
		dprintf(2, "Invalid type of arguments 1 or 3\n");
		return (84);
	}
	else if (atoi(av[2]) < 2 || atoi(av[4]) < 1) {
		dprintf(2, "Invalid number of philosopher\n");
		return (84);
	}
	if (loop(atoi(av[2]), atoi(av[4])) == 84)
		return (84);
	RCFCleanup();
	return (0);
}
