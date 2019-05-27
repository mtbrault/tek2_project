/*
** EPITECH PROJECT, 2018
** IRC
** File description:
** init list
*/

#include "get_next_line.h"
#include "serveur.h"

static int	handle_client(int fd, clients_list_t **cli, channel_t *chann)
{
	char		*buff;
	char		**cmds;

	if (get_next_line(fd, &buff) == 0 || buff == NULL) {
		buff = get_info(fd, *cli);
		del_elem_from_list(fd, cli);
		if (*cli == NULL)
			return (0);
		for (clients_list_t *tmp = *cli; tmp; tmp = tmp->next)
			dprintf(tmp->fd,
				":%s!*@localhost QUIT :Socket close\n", buff);
		return (0);
	}
	cmds = my_str_to_wordtab(buff, ' ');
	if (cmds == NULL || !cmds[0])
		return (-1);
	return (check_function(fd, cli, cmds, chann));
}

void	launch_client(all_server_t *all, channel_t *chann)
{
	if (FD_ISSET(3, &all->readfds))
		get_client(all);
	for (all->tmp = all->clients_list; all->tmp;
		all->tmp = all->tmp->next) {
		if (FD_ISSET(all->tmp->fd, &all->readfds))
			handle_client(all->tmp->fd, &all->clients_list, chann);
	}
}

clients_list_t	*add_client2(clients_list_t *list, int fd)
{
	list->last->next = malloc(sizeof(clients_list_t));
	list->last = list->last->next;
	list->last->next = NULL;
	list->last->fd = fd;
	list->last->find = 0;
	list->last->channel = malloc(sizeof(channel_t));
	list->last->channel->channel = "";
	list->last->channel->next = NULL;
	list->last->name = "*";
	return (list);
}
