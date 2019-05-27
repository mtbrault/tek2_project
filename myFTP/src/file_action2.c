/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** file_action2
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "myftp.h"

void	dele(ftp_t *ftp, char **cmd)
{
	int	ret;

	if (!cmd[1] || cmd[2])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else {
		for (int i = 0; cmd[1][i] != '\0'; i++) {
			if (cmd[1][i] == '\r')
				cmd[1][i] = '\0';
		}
		ret = remove(cmd[1]);
		if (ret == -1)
			print_msg(550, ftp->client_fd);
		else
			print_msg(250, ftp->client_fd);
	}
}

void	pwd(ftp_t *ftp, char **cmd)
{
	char	*pwd;
	char	*home;
	char	*final;

	if (cmd[1])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else {
		pwd = get_pwd(getcwd(NULL, 0));
		home = get_pwd(ftp->home);
		final = (strcmp(pwd, home) == 0) ? "" : pwd;
		dprintf(ftp->client_fd, "257 \"/%s\"\n", final);
		free(pwd);
		free(home);
	}
}
