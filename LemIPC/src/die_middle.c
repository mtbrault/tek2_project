/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** ai
*/

#include <stdio.h>
#include "lemipc.h"

static int	move_horizontaly(int move, int *map, int pos)
{
	if (move == 0)
		return (pos);
	else if (move < 0) {
		if (map[pos - 1] == 0)
			return (pos - 1);
		else
			return (pos);
	} else {
		if (map[pos + 1] == 0)
			return (pos + 1);
		else
			return (pos);
	}
}

static int	move_verticaly(int move, int *map, int pos)
{
	if (move == 0)
		return (pos);
	if (move < 0) {
		if (map[pos - WIDTH] == 0)
			return (pos - WIDTH);
		else
			return (pos);
	} else {
		if (map[pos + WIDTH] == 0)
			return (pos + WIDTH);
		else
			return (pos);
	}
}

static int	abs(int x)
{
	return ((x < 0) ? -x : x);
}

int	die_middle(lemipc_t *keys, int *map, int pos)
{
	int	middle_x = (WIDTH / 2) - 1;
	int	middle_y = HEIGHT / 2;
	int	player_x = convert_pos(pos, 0);
	int	player_y = convert_pos(pos, 1);
	int	dest_x = middle_x - player_x;
	int	dest_y = middle_y - player_y;
	int	dir;

	if (dest_x != 0 && (abs(dest_x) <= abs(dest_y) || dest_y == 0)) {
		dir = move_horizontaly(dest_x, map, pos);
	} else {
		dir = move_verticaly(dest_y, map, pos);
	}
	map[pos] = 0;
	map[dir] = keys->team;
	return (dir);
}
