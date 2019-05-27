/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** loop
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "myftp.h"

cmd_t	cmd_table[CMD_SIZE] =
{
	{"USER", &user},
	{"PASS", &pass},
	{"CWD", &cwd},
	{"CDUP", &cdup},
	{"DELE", &dele},
	{"PWD", &pwd},
	{"PASV", &pasv},
	{"PORT", &port},
	{"HELP", &help},
	{"NOOP", &noop},
	{"RETR", &retr},
	{"STOR", &stor},
	{"LIST", &list},
	{"QUIT", &quit}
};

void	help(ftp_t *ftp, char **cmd)
{
	(void)cmd;
	if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else {
		dprintf(ftp->client_fd, "214 Following command :\n");
		for (int i = 0; i < CMD_SIZE; i++) {
			dprintf(ftp->client_fd, "%s", cmd_table[i].cmd);
			if (i + 1 < CMD_SIZE)
				dprintf(ftp->client_fd, " ");
		}
		dprintf(ftp->client_fd, "\n214 Help OK.\n");
	}
}

static int	compar(ftp_t *ftp, char **tab)
{
	int	find = 0;
	int	loop = 0;

	for (int i = 0; i < CMD_SIZE; i++) {
		if (my_strcmp(tab[0], cmd_table[i].cmd) == 0) {
			cmd_table[i].func(ftp, tab);
			find = 1;
		}
		if (my_strcmp(tab[0], "QUIT") == 0)
			loop = 1;
	}
	if (find == 0)
		print_msg(500, ftp->client_fd);
	return (loop);
}

static void	exec_cmd(ftp_t *ftp)
{
	char	cmd[4200];
	char	**tab;
	int	size = 0;
	int	loop = 0;

	while (loop == 0 && (size = read(ftp->client_fd, cmd, 4200))) {
		if (cmd[0] == ' ') {
			print_msg(500, ftp->client_fd);
			continue;
		}
		cmd[size] = '\0';
		tab = my_str_to_wordtab(cmd, ' ');
		my_upper(tab[0]);
		loop = compar(ftp, tab);
		for (int i = 0; i < 4200; i++)
			cmd[i] = '\0';
	}
	close(ftp->client_fd);
}

int	loop(ftp_t *ftp)
{
	socklen_t	size;
	struct sockaddr	*tmp;

	while (1) {
		tmp = (struct sockaddr *)&ftp->client_sin;
		size = sizeof(ftp->client_sin);
		ftp->client_fd = accept(ftp->server_fd, tmp, &size);
		if (ftp->client_fd == -1) {
			close(ftp->server_fd);
			return (0);
		}
		if (fork() == 0) {
			print_msg(220, ftp->client_fd);
			exec_cmd(ftp);
			exit(0);
		}
		else
			close(ftp->client_fd);
	}
	return (0);
}
