/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** tools2
*/

#include <stdio.h>
#include <ctype.h>
#include "myftp.h"

int	my_strcmp(char *s1, char *s2)
{
	int	i = 0;

	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] != s2[i])
			return (1);
		i += 1;
	}
	if (s1[i + 1] == '\n')
		return (0);
	return (s1[i] - s2[i]);
}

void	read_dir(DIR *dir, int fd)
{
	struct dirent	*file;

	while ((file = readdir(dir))) {
		if (file->d_name[0] != '.')
			dprintf(fd, "%s\n", file->d_name);
	}
	closedir(dir);
}

void	my_upper(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		str[i] = toupper(str[i]);
	}
}
