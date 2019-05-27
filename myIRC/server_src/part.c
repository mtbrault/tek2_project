/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** part cmd
*/

#include "serveur.h"

static void	print_part(clients_list_t *cli, int fd, char *chann)
{
	clients_list_t	*tmp;

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (!exist_channel(chann, tmp->channel) || tmp->fd == fd) {
			dprintf(tmp->fd, ":%s!*@localhost PART %s\n",
				get_info(fd, cli), chann);
		}
	}
}

static void	part_msg(channel_t *list, int fd, clients_list_t *cli,
			char *ch)
{
	if (!strcmp(list->channel, ch)) {
		list->channel = "";
		print_part(cli, fd, ch);
	}
	else {
		print_msg("442", get_info(fd, cli), ch, fd);
		dprintf(fd, " :You're not on that channel\n");
	}
}

void	part(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	clients_list_t	*tmp;
	channel_t	*list;

	if (!cmd[1]) {
		print_msg("461", get_info(fd, cli), "PART :Need param\n", fd);
		return;
	} else if (exist_channel(cmd[1], chann) == 1) {
		print_msg("403", get_info(fd, cli), cmd[1], fd);
		dprintf(fd, " :No such channel\n");
		return;
	}
	for (tmp = cli; tmp && tmp->fd != fd; tmp = tmp->next);
	for (list = tmp->channel; list->next &&
		strcmp(list->next->channel, cmd[1]); list = list->next);
	if (!list->next)
		part_msg(list, fd, cli, cmd[1]);
	else {
		list->next = list->next->next;
		print_part(cli, fd, cmd[1]);
	}
}
