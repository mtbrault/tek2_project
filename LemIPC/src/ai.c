/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** ai
*/

#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

static int	is_place_free(int *map, int pos, int dir)
{
	if (map[dir] != 0)
		return (pos);
	return (dir);
}

static int	ai_random(lemipc_t *keys, int *map, int pos)
{
	int	random = (rand() % 4) + 1;
	int	dir = pos;

	if (random == 1 && convert_pos(pos, 1) != 0)
		dir = is_place_free(map, pos, pos - WIDTH);
	else if (random == 2 && convert_pos(pos, 0) != (WIDTH - 1))
		dir = is_place_free(map, pos, pos + 1);
	else if (random == 3 && convert_pos(pos, 1) != (HEIGHT - 1))
		dir = is_place_free(map, pos, pos + WIDTH);
	else if (random == 4 && convert_pos(pos, 0) != 0)
		dir = is_place_free(map, pos, pos - 1);
	map[pos] = 0;
	map[dir] = keys->team;
	return (dir);
}

int	ai(lemipc_t *keys, int *map, int pos)
{
	if (keys->ai_type == 1)
		return (die_middle(keys, map, pos));
	else
		return (ai_random(keys, map, pos));
}
