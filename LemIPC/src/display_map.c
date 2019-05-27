/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** display map
*/

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "lemipc.h"

static void	print_line()
{
	printf("+");
	for (int i = 0; i < WIDTH; i++)
		printf("-");
	printf("+\n");
}

void	display_map(int *map)
{
	print_line();
	for (int y = 0; y < HEIGHT; y++) {
		printf("|");
		for (int x = 0; x < WIDTH; x++) {
			if (map[y * WIDTH + x] == 0)
				printf(" ");
			else
				printf("%d", map[y * WIDTH + x]);
		}
		printf("|\n");
	}
	print_line();
}
