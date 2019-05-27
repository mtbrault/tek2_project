/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** main file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <time.h>
#include "lemipc.h"

static lemipc_t		*init_struct(int ac, char **av)
{
	lemipc_t	*key;

	if (ac != 3) {
		if (ac == 2 && strcmp(av[1], "--help") == 0)
			exit(display_usage());
		else if (ac != 4 || atoi(av[3]) != 1)
			return (my_puternull(INVALID_NB_ARG));
	}
	key = malloc(sizeof(lemipc_t));
	if (key == NULL)
		return (NULL);
	key->key = ftok(av[1], 0);
	key->team = atoi(av[2]);
	key->ai_type = (ac == 4 && atoi(av[3]) == 1) ? 1 : 0;
	if (key->team <= 0 || check_is_int(av[2]) == 1)
		return (my_puternull(INVALID_NB_TEAM));
	else if (key->key == -1)
		return (my_puternull(INVALID_FILE));
	return (key);
}

int	main(int ac, char **av)
{
	lemipc_t	*key = init_struct(ac, av);
	int		return_value = 0;

	if (key == NULL)
		return (84);
	srand(time(NULL));
	return_value = init_id(key);
	free(key);
	return (return_value);
}
