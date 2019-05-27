/*
** EPITECH PROJECT, 2018
** gnl2
** File description:
** gnl2
*/

#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"

int	vrf(char *str)
{
	int	i;

	i = 0;
	while (str[i]) {
		if (str[i] == '\n' || str[i] == '\r')
			return (i);
		++i;
	}
	return (-1);
}

char	*erase_leaks(char *str, char *st_str)
{
	char	*tmp;

	tmp = strjoin(str, st_str);
	free(str);
	str = strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (str);
}
