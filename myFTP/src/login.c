/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** command
*/

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "myftp.h"

void	user(ftp_t *ftp, char **cmd)
{
	if (!cmd[1] || cmd[2] || ftp->user == 1)
		print_msg(504, ftp->client_fd);
	else if (my_strcmp(cmd[1], "Anonymous") == 0) {
		print_msg(331, ftp->client_fd);
		ftp->user = 1;
	}
	else {
		print_msg(331, ftp->client_fd);
		ftp->user = 2;
	}
}

void	pass(ftp_t *ftp, char **cmd)
{
	if (!cmd[1] || cmd[2])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0)
		print_msg(503, ftp->client_fd);
	else if (!cmd[1] || my_strcmp(cmd[1], "") == 0) {
		if (ftp->user == 2)
			print_msg(530, ftp->client_fd);
		else {
			ftp->pass = 1;
			print_msg(230, ftp->client_fd);
		}
	}
	else {
		print_msg(530, ftp->client_fd);
		ftp->user = 0;
	}
}

void	cwd(ftp_t *ftp, char **cmd)
{
	int	ret;

	if (!cmd[1] || cmd[2])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else {
		cmd[1][strlen(cmd[1]) - 2] = '\0';
		ret = chdir(cmd[1]);
		if (ret == -1)
			print_msg(550, ftp->client_fd);
		else
			print_msg(250, ftp->client_fd);
	}
}

void	cdup(ftp_t *ftp, char **cmd)
{
	int	ret;

	if (cmd[1])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else {
		ret = chdir(ftp->home);
		if (ret == -1)
			print_msg(550, ftp->client_fd);
		else
			print_msg(250, ftp->client_fd);
	}
}

void	quit(ftp_t *ftp, char **cmd)
{
	if (cmd[1])
		print_msg(504, ftp->client_fd);
	else {
		ftp->user = 0;
		ftp->pass = 0;
		print_msg(221, ftp->client_fd);
	}
	
}
