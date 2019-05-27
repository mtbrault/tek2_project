/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** loop file
*/

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdio.h>
#include "lemipc.h"

static int	game_end(int *map)
{
	int	team = 10;

	for (int i = 0; i < (WIDTH * HEIGHT); i++) {
		if (map[i] != 0) {
			team = map[i];
			for (int s = (i + 1); s < (WIDTH * HEIGHT); s++) {
				if (map[s] != 0 && map[s] != map[i])
					return (0);
			}
		}
	}
	return (team);
}

static void	delete_ipcs(lemipc_t *keys, int i)
{
	printf("L'équipe %d a gagné !\n", i);
	shmctl(keys->shm, IPC_RMID, NULL);
	semctl(keys->sem, 0, IPC_RMID);
	msgctl(keys->msg, IPC_RMID, NULL);
}

void	loop(lemipc_t *keys, int *map, int pos, int first)
{
	int	i = 0;
	int	alive = 1;

	while (i == 0) {
		block(keys->sem, 1);
		if (alive == 1) {
			pos = ai(keys, map, pos);
			alive = is_alive(map, pos, keys);
			if (alive == 0)
				map[pos] = 0;
		}
		i = game_end(map);
		if (first == 1)
			display_map(map);
		block(keys->sem, 2);
		usleep(75000);
	}
	if (first == 1)
		delete_ipcs(keys, i);
}
