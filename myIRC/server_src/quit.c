/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** channel cmd
*/

#include <stdlib.h>
#include "serveur.h"

void	quit(clients_list_t **cli, char **cmd, int fd)
{
	clients_list_t	*tmp;
	char		*name = get_info(fd, *cli);

	del_elem_from_list(fd, cli);
	for (tmp = *cli; tmp; tmp = tmp->next) {
		dprintf(tmp->fd, ":%s!*@localhost QUIT :", name);
		if (!cmd[1]) {
			dprintf(tmp->fd, "Disconncetion message\n");
			continue;
		}
		for (int i = 1; cmd[i]; i++) {
			dprintf(tmp->fd, "%s", cmd[i]);
			if (cmd[i + 1])
				dprintf(tmp->fd, " ");
		}
		dprintf(tmp->fd, "\n");
	}
}
