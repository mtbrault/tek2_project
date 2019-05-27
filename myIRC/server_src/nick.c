/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** nick cmd
*/

#include "serveur.h"

static void	check_aff(clients_list_t *cli, int fd)
{
	clients_list_t	*tmp;

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (tmp->fd == fd && tmp->find == 1 && strcmp(tmp->name, "*"))
			print_msg("001", get_info(fd, cli), ":IS OK\n", fd);
	}
}

static void	nick_next(clients_list_t *cli, char **cmd, int fd)
{
	clients_list_t	*tmp;
	char		*stock = get_info(fd, cli);

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (strcmp(stock, "*"))
			dprintf(tmp->fd, ":%s!*@localhost NICK %s\n",
				stock, cmd[1]);
		if (tmp->fd == fd)
			tmp->name = cmd[1];
	}
	check_aff(cli, fd);
}

void	user(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	clients_list_t	*tmp;

	(void)chann;
	if (!cmd[1] || !cmd[2] || !cmd[3] || !cmd[4])
		print_msg("461", get_info(fd, cli),
			"USER :Not enough parameters\n", fd);
	else {
		for (tmp = cli; tmp; tmp = tmp->next) {
			if (tmp->fd == fd) {
				tmp->find = 1;
				check_aff(cli, fd);
			}
		}
	}
}

void	nick(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	clients_list_t	*tmp;

	(void)chann;
	if (!cmd[1]) {
		print_msg("431", get_info(fd, cli), ":No nickname given\n", fd);
		return;
	}
	for (tmp = cli; tmp; tmp = tmp->next) {
		if (!strcmp(tmp->name, cmd[1]) || cmd[1][0] == '#') {
			print_msg("433", get_info(fd, cli), cmd[1], fd);
			dprintf(fd, " :Nickname is used\n");
			return;
		}
	}
	nick_next(cli, cmd, fd);
}
