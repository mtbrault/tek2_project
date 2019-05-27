/*
** EPITECH PROJECT, 2018
** strace
** File description:
** main file
*/

#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include "strace.h"

int	main(int ac, char **av, char **env)
{
	int	is_s = 0;

	if (ac == 1)
		return (my_puterror(BAD_NB_ARGS));
	for (int i = 1; i < ac; i++) {
		if (strcmp(av[i], "-s") == 0)
			is_s = 1;
		else if (strcmp(av[i], "-p") == 0) {
			if (i == (ac - 1) || is_number(av[i + 1]) == 1)
				return (my_puterror(BAD_PID));
			ptrace(PTRACE_ATTACH, atoi(av[i + 1]), NULL, NULL);
			return (start_strace(atoi(av[i + 1]), is_s));
		}
		else
			return (launch_program(av + i, env, is_s));
	}
	return (0);
}
