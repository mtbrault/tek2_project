/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** privmsg file
*/

#include <stdlib.h>
#include "serveur.h"

static void	print_loop(int fd, char **cmd)
{
	for (int i = 2; cmd[i]; i++) {
		dprintf(fd, "%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			dprintf(fd, " ");
	}
	dprintf(fd, "\n");
}

static void	send_msg_private(clients_list_t *cli, char **cmd, int fd)
{
	clients_list_t	*tmp;
	int		find = 0;

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (strcmp(tmp->name, cmd[1]) == 0 && tmp->fd != fd) {
			find = 1;
			dprintf(tmp->fd, ":%s PRIVMSG : ", get_info(fd, cli));
			return (print_loop(tmp->fd, cmd));
		}
	}
	if (find == 0) {
		print_msg("401", get_info(fd, cli), cmd[1], fd);
		dprintf(fd, " :No such nick\n");
	}
}

static void	send_msg_channel(clients_list_t *cli, char **cmd, int fd)
{
	clients_list_t	*tmp;

	for (tmp = cli; tmp && tmp->fd != fd; tmp = tmp->next);
	if (exist_channel(cmd[1], tmp->channel)) {
		print_msg("442", get_info(fd, cli), cmd[1], fd);
		dprintf(fd, " :You're not on that channel\n");
		return;
	}
	for (tmp = cli; tmp; tmp = tmp->next) {
		if (!exist_channel(cmd[1], tmp->channel) && tmp->fd != fd) {
			dprintf(tmp->fd, ":%s %s : ",
				get_info(fd, cli), cmd[1]);
			print_loop(tmp->fd, cmd);
		}
	}
}

void	msg(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	if (!cmd[1])
		return (print_msg("411", get_info(fd, cli),
				":No recipient given\n", fd));
	else if (!cmd[2])
		return (print_msg("412", get_info(fd, cli),
				":No text to send\n", fd));
	else if (cmd[1][0] == '#' || cmd[1][0] == '&') {
		if (exist_channel(cmd[1], chann)) {
			print_msg("403", get_info(fd, cli), cmd[1], fd);
			dprintf(fd, " :No such channel\n");
			return;
		}
		return (send_msg_channel(cli, cmd, fd));
	}
	return (send_msg_private(cli, cmd, fd));
}
