/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** init id
*/

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include "lemipc.h"

static int	init_player(int *map, lemipc_t *keys)
{
	int	random = rand() % (WIDTH * HEIGHT);

	block(keys->sem, 1);
	if (map_is_full(map) == 0) {
		block(keys->sem, 2);
		exit(0);
	}
	while (map[random] != 0) {
		random = rand() % (WIDTH * HEIGHT);
	}
	map[random] = keys->team;
	block(keys->sem, 2);
	return (random);
}


static void	init_map(int *map)
{
	for (int i = 0; i < (WIDTH * HEIGHT); i++)
		map[i] = 0;
}

static int	get_pos(lemipc_t *keys, int *map, int first)
{
	int	pos = init_player(map, keys);
	int	i = 1;

	while (i == 1) {
		block(keys->sem, 1);
		i = is_alone(map, keys);
		if (first == 1)
			display_map(map);
		block(keys->sem, 2);
	}
	return (pos);
}

static int	create_game(lemipc_t *keys)
{
	int	*map;
	int	pos;

	keys->shm = shmget(keys->key, sizeof(int) * WIDTH * HEIGHT,
			IPC_CREAT | SHM_R | SHM_W);
	keys->msg = msgget(keys->key, IPC_CREAT | SHM_R | SHM_W);
	keys->sem = semget(keys->key, 1, IPC_CREAT | SHM_R | SHM_W);
	map = (int *)shmat(keys->shm, NULL, IPC_CREAT | SHM_R | SHM_W);
	if (map == (void *)-1 || keys->shm == -1 || keys->sem == -1
	|| keys->msg == -1)
		return (84);
	semctl(keys->sem, 0, SETVAL, 1);
	init_map(map);
	pos = get_pos(keys, map, 1);
	loop(keys, map, pos, 1);
	return (0);
}

int	init_id(lemipc_t *keys)
{
	int	*map;
	int	pos;

	keys->shm = shmget(keys->key, sizeof(int) * WIDTH * HEIGHT,
			SHM_R | SHM_W);
	if (keys->shm == -1)
		return (create_game(keys));
	keys->sem = semget(keys->key, 1, SHM_R | SHM_W);
	keys->msg = msgget(keys->key, SHM_R | SHM_W);
	map = (int *)shmat(keys->shm, NULL, SHM_R | SHM_W);
	if (keys->sem == -1 || keys->msg == -1 || map == (void *)-1)
		return (my_puterror("Problem to get the id\n"));
	pos = get_pos(keys, map, 0);
	loop(keys, map, pos, 0);
	return (0);
}
