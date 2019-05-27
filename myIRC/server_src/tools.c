/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** get info
*/

#include <stdlib.h>
#include "serveur.h"

void	print_msg(char *code, char *name, char *msg, int fd)
{
	if (strcmp(name, ""))
		dprintf(fd, "%s %s %s", code, name, msg);
	else
		dprintf(fd, "%s %s", code, msg);
}

char	*get_info(int fd, clients_list_t *cli)
{
	clients_list_t	*tmp;

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (tmp->fd == fd) {
			return (tmp->name);
		}
	}
	return (NULL);
}

int	exist_channel(char *chann, channel_t *list)
{
	channel_t	*tmp;

	for (tmp = list; tmp; tmp = tmp->next) {
		if (tmp->channel != NULL && !strcmp(chann, tmp->channel))
			return (0);
	}
	return (1);
}

int	send_msg(int fd, clients_list_t *cli, char **cmd, char *chann)
{
	clients_list_t	*tmp;

	for (tmp = cli; tmp; tmp = tmp->next) {
		if (exist_channel(chann, tmp->channel) == 0 && tmp->fd != fd) {
			dprintf(tmp->fd, "%s %s : ", chann, get_info(fd, cli));
			for (int i = 2; cmd[i] != NULL; i ++) {
				dprintf(tmp->fd, "%s", cmd[i]);
				if (cmd[i + 1] != NULL)
					dprintf(tmp->fd, " ");
			}
			dprintf(tmp->fd, "\n");
		}
	}
	return (0);
}

void	del_elem_from_list(int fd, clients_list_t **cli)
{
	clients_list_t	*tmp;

	close(fd);
	if ((*cli)->fd == fd) {
		(*cli)->fd = 0;
		(*cli)->name = "";
		return;
	}
	for (tmp = (*cli); tmp->next; tmp = tmp->next) {
		if (fd == tmp->next->fd) {
			if (tmp->next == (*cli)->last) {
				(*cli)->last = tmp;
				(*cli)->last->next = NULL;
			} else {
				tmp->next = tmp->next->next;
			}
			return;
		}
	}
}
