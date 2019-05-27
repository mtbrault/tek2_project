/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** tools file
*/

#include <stdio.h>
#include "lemipc.h"

int	display_usage()
{
	printf("USAGE\n\t./lemipc PATH TEAM_NUMBER\n");
	printf("\nDESCRIPTION\n\tPATH\t\tpath you'll give to ftok\n");
	printf("\tTEAM_NUMBER\tteam number of the current champion");
	printf(" (greater than 0)\n");
	return (0);
}

void	*my_puternull(char *str)
{
	dprintf(2, str);
	return (NULL);
}

int	my_puterror(char *str)
{
	dprintf(2, str);
	return (84);
}

int	check_is_int(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

int	convert_pos(int val, int opt)
{
	if (opt == 0)
		return (val % WIDTH);
	else if (opt == 1)
		return (val / HEIGHT);
	else
		return (-1);
}
