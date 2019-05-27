/*
** EPITECH PROJECT, 2018
** handle_client
** File description:
** handle_clien
*/

#include "get_next_line.h"
#include "serveur.h"

cmd_t	cmd_table[CMD_SIZE] =
{
	{"NICK", &nick},
	{"USER", &user},
	{"LIST", &list},
	{"JOIN", &join},
	{"PART", &part},
	{"USERS", &users},
	{"NAMES", &names},
	{"PRIVMSG", &msg}
};

int	check_function(int fd, clients_list_t **cli,
				char **cmd, channel_t *chann)
{
	if (strcmp(get_info(fd, *cli), "*") == 0 && strcmp(cmd[0], "NICK")
		&& strcmp(cmd[0], "USER")) {
		dprintf(fd, "Please select a nickname with /nick\n");
		return (-1);
	}
	else if (strcmp("QUIT", cmd[0]) == 0) {
		quit(cli, cmd, fd);
		return (0);
	}
	for (int i = 0; i < CMD_SIZE; i++) {
		if (!strcmp(cmd[0], cmd_table[i].cmd)) {
			cmd_table[i].func(*cli, cmd, fd, chann);
			return (0);
		}
	}
	dprintf(fd, "This command doesn't exit\n");
	return (-1);
}

void	get_client(all_server_t *all_server)
{
	all_server->client_fd = accept(all_server->server.fd,
		(struct sockaddr *)&all_server->server.s_in_client,
			&all_server->server.s_in_size);
	if (all_server->client_fd != -1)
		all_server->clients_list =
			add_client(all_server->clients_list,
				all_server->client_fd);
}

static int	get_max_fd(clients_list_t *list)
{
	clients_list_t	*tmp;
	int		stock = 0;

	if (list == NULL)
		return (4);
	for (tmp = list; tmp; tmp = tmp->next) {
		if (tmp->fd > stock)
			stock = tmp->fd;
	}
	if (stock <= 3)
		return (4);
	return (stock + 1);
}

int handle_clients(all_server_t *all_server, channel_t *chann)
{
	FD_ZERO(&all_server->readfds);
	FD_SET(3, &all_server->readfds);
	for (all_server->tmp = all_server->clients_list;
		all_server->tmp; all_server->tmp = all_server->tmp->next)
		FD_SET(all_server->tmp->fd, &all_server->readfds);
	if (select(get_max_fd(all_server->clients_list),
		&all_server->readfds, NULL, NULL, NULL) == -1) {
			printf("error\n");
			all_server->error = 1;
		}
	else
		launch_client(all_server, chann);
	return (0);
}
