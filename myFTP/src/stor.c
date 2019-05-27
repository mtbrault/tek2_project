/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** stor
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "myftp.h"

static void	stor_next(int file_fd, ftp_t *ftp)
{
	int	fd;
	char	buff[1];

	fd = accept(ftp->pasv_fd, NULL, NULL);
	if (fd == -1)
		return (print_msg(451, ftp->client_fd));
	print_msg(150, ftp->client_fd);
	while (read(fd, buff, 1) > 0)
		write(file_fd, buff, 1);
	print_msg(226, ftp->client_fd);
	close(file_fd);
	close(ftp->pasv_fd);
	ftp->mode = 0;
}

void	stor(ftp_t *ftp, char **cmd)
{
	int	fd;

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
		fd = open(cmd[1], O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (fd == -1)
			return (print_msg(550, ftp->client_fd));
		stor_next(fd, ftp);
		print_msg(150, ftp->client_fd);
		print_msg(226, ftp->client_fd);
	}
}
