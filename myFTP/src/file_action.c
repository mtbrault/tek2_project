/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** builtins2 file
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "myftp.h"

static void	retr_next(ftp_t *ftp, FILE *file)
{
	char	c;
	int	fd;

	fd = accept(ftp->pasv_fd, NULL, NULL);
	if (fd == -1)
		return (print_msg(451, ftp->client_fd));
	print_msg(150, ftp->client_fd);
	while ((c = fgetc(file)) != EOF)
		dprintf(fd, "%c", c);
	print_msg(226, ftp->client_fd);
	close(fd);
	close(ftp->pasv_fd);
	ftp->mode = 0;
}

void	retr(ftp_t *ftp, char **cmd)
{
	FILE	*file;

	if (!cmd[1] || cmd[2])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else if (ftp->mode == 0)
		print_msg(425, ftp->client_fd);
	else {
		for (int i = 0; cmd[1][i] != '\0'; i++) {
			if (cmd[1][i] == '\r')
				cmd[1][i] = '\0';
		}
		file = fopen(cmd[1], "r");
		if (file == NULL)
			return (print_msg(550, ftp->client_fd));
		retr_next(ftp, file);
	}
}

static void	list_next(ftp_t *ftp, int fd, char **cmd)
{
	DIR	*dir;

	dir = opendir((!cmd[1]) ? "." : cmd[1]);
	if (dir == NULL)
		return (print_msg(550, ftp->client_fd));
	read_dir(dir, fd);
	print_msg(226, ftp->client_fd);
	close(fd);
	close(ftp->pasv_fd);
	ftp->mode = 0;
}

void	list(ftp_t *ftp, char **cmd)
{
	int	fd;

	if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else if (ftp->mode == 0)
		print_msg(425, ftp->client_fd);
	else {
		fd = accept(ftp->pasv_fd, NULL, NULL);
		print_msg(150, ftp->client_fd);
		if (fd == -1)
			return (print_msg(451, ftp->client_fd));
		if (cmd[1]) {
			for (int i = 0; cmd[1][i] != '\0'; i++) {
				if (cmd[1][i] == '\r')
					cmd[1][i] = '\0';
			}
		}
		list_next(ftp, fd, cmd);
	}
}
