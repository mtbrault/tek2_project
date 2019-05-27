/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** join function
*/

#include <stdlib.h>
#include "serveur.h"

static void	join_msg(clients_list_t *cli, int fd,
			char **c, channel_t *chann)
{
	clients_list_t	*tmp;

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (!exist_channel(c[1], tmp->channel)) {
			dprintf(tmp->fd, ":%s!*@localhost JOIN %s\n",
				get_info(fd, cli), c[1]);
			if (tmp->fd == fd) {
				print_msg("331", get_info(fd, cli), c[1], fd);
				dprintf(fd, " :No topic is set\n");
				names(cli, c, fd, chann);
			}
		}
	}
}

static void	add_channel(clients_list_t *cli, int fd,
			char **cmd, channel_t *chann)
{
	channel_t	*list;
	clients_list_t	*tmp;

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (tmp->fd == fd) {
			if (exist_channel(cmd[1], tmp->channel) == 0)
				return;
			for (list = tmp->channel; list->next;
				list = list->next);
			list->next = malloc(sizeof(channel_t));
			if (list->next == NULL)
				return;
			list->next->next = NULL;
			list->next->channel = cmd[1];
		}
	}
	join_msg(cli, fd, cmd, chann);
}

static void	new_chann(channel_t *tmp, char *name)
{
	tmp->next = malloc(sizeof(channel_t));
	if (tmp->next == NULL)
		return;
	tmp->next->next = NULL;
	tmp->next->channel = name;
}

void	join(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	channel_t	*tmp;

	if (!cmd[1]) {
		print_msg("461", get_info(fd, cli), "JOIN :Need param\n", fd);
		return;
	} else if (cmd[1][0] != '#' && cmd[1][0] != '&') {
		print_msg("475", get_info(fd, cli), cmd[1], fd);
		dprintf(fd, " Channel must start with # or &\n");
		return;
	}
	for (tmp = chann; tmp; tmp = tmp->next) {
		if (!strcmp(tmp->channel, cmd[1]))
			return (add_channel(cli, fd, cmd, chann));
	}
	for (tmp = chann; tmp->next != NULL; tmp = tmp->next);
	new_chann(tmp, cmd[1]);
	add_channel(cli, fd, cmd, chann);
}
