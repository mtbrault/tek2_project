/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** tools
*/

#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "myftp.h"

int	my_puterror(char *str, ftp_t *ftp)
{
	dprintf(2, str);
	if (ftp != NULL) {
		if (ftp->server_fd != -1)
			close(ftp->server_fd);
		else if (ftp->client_fd != -1)
			close(ftp->client_fd);
		free(ftp);
	}
	return (84);
}

int	check_is_num(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

int	error_handling(int ac, char **av, ftp_t *ftp)
{
	int	i;

	ftp->server_fd = -1;
	ftp->client_fd = -1;
	ftp->user = 0;
	ftp->pass = 0;
	ftp->mode = 0;
	if (ac != 3)
		return (my_puterror(BAD_NB_ARG, ftp));
	for (i = 0; av[2][i + 1] != '\0'; i++);
	if (check_is_num(av[1]) == 1)
		return (my_puterror(BAD_PORT, ftp));
	else if (chdir(av[2]) == -1)
		return (my_puterror(BAD_PATH, ftp));
	ftp->home = getcwd(NULL, 0);
	return (0);
}
