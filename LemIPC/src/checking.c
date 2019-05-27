/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** checking functions
*/

#include "lemipc.h"

int	is_alone(int *map, lemipc_t *keys)
{
	for (int i = 0; i < (WIDTH * HEIGHT); i++) {
		if (map[i] != 0 && map[i] != keys->team) {
			return (0);
		}
	}
	return (1);
}

int	map_is_full(int *map)
{
	for (int i = 0; i < (WIDTH * HEIGHT); i++) {
		if (map[i] == 0)
			return (1);
	}
	return (0);
}
