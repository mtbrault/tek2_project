/*
** EPITECH PROJECT, 2018
** strace
** File description:
** tools file
*/

#include <unistd.h>
#include <string.h>

int	is_number(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

int	my_puterror(char *str)
{
	write(2, str, strlen(str));
	return (84);
}
