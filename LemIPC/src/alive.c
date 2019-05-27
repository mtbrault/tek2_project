/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** check if process is alive
*/

#include "lemipc.h"

static int	two_player_around(int near[8], int player_team)
{
	for (int i = 0; i < 8; i++) {
		for (int s = 0; s < 8; s++) {
			if (near[s] == near[i] && s != i
			&& near[s] != player_team && near[s] != 0)
				return (1);
		}
	}
	return (0);
}

static int	alive_middle(int pos)
{
	if (convert_pos(pos, 0) == (WIDTH / 2 - 1)
	&& convert_pos(pos, 1) == HEIGHT / 2)
		return (0);
	return (1);
}

static int	alive_normal(int *map, int pos, int player_team)
{
	int	near[8];

	near[0] = (convert_pos(pos, 0) == (WIDTH - 1)) ? 0 : map[pos + 1];
	near[1] = (convert_pos(pos, 0) == (WIDTH - 1) || pos < WIDTH)
		? 0 : map[pos + 1 - WIDTH];
	near[2] = (pos < WIDTH) ? 0 : map[pos - WIDTH];
	near[3] = (pos < WIDTH || convert_pos(pos, 0) == 0) ? 0
		: map[pos - 1 - WIDTH];
	near[4] = (convert_pos(pos, 0) == 0) ? 0 : map[pos - 1];
	near[5] = (convert_pos(pos, 0) == 0 || convert_pos(pos, 1)
		== (HEIGHT - 1)) ? 0 : map[pos - 1 + WIDTH];
	near[6] = (convert_pos(pos, 1) == (HEIGHT - 1))
		? 0 : map[pos + WIDTH];
	near[7] = (convert_pos(pos, 1) == (HEIGHT - 1) || convert_pos(pos, 0)
		== (WIDTH - 1)) ? 0 : map[pos + 1 + WIDTH];
	if (two_player_around(near, player_team) == 1)
		return (0);
	return (1);
}

int	is_alive(int *map, int pos, lemipc_t *keys)
{
	if (keys->ai_type == 1)
		return (alive_middle(pos));
	else
		return (alive_normal(map, pos, keys->team));
}
