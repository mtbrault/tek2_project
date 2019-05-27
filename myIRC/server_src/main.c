/*
** EPITECH PROJECT, 2018
** dsqdqs
** File description:
** dqs
*/

#include "serveur.h"

clients_list_t	*add_client(clients_list_t *clients_list, int fd)
{
	if (clients_list == NULL) {
		clients_list = malloc(sizeof(clients_list_t));
		clients_list->fd = fd;
		clients_list->channel = malloc(sizeof(channel_t));
		clients_list->channel->channel = "";
		clients_list->channel->next = NULL;
		clients_list->name = "*";
		clients_list->find = 0;
		clients_list->next = NULL;
		clients_list->last = clients_list;
	}
	else
		return (add_client2(clients_list, fd));
	return (clients_list);
}

static int bind_server(server_t *server)
{
	if (bind(server->fd, (const struct sockaddr *)&server->s_in,
		sizeof(server->s_in)) == -1) {
		printf("Error: bind failed\n");
		if (close(server->fd) == -1) {
			printf("Error: close failed\n");
			return (84);
		}
		return (84);
	}
	if (listen(server->fd, 42) == -1) {
		printf("Error: listen failed\n");
		if (close(server->fd) == -1) {
			printf("Error: close failed\n");
			return (84);
		}
		return (84);
	}
	return (0);
}

static int init_serveur(int port, server_t *server)
{
	server->s_in_size = sizeof(server->s_in_client);
	server->pe = getprotobyname("TCP");
	if (!server->pe) {
		printf("Error getprotobyname failed\n");
		return (84);
	}
	server->fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto);
	if (server->fd == -1) {
		printf("Error: fd failed\n");
		return (84);
	}
	server->s_in.sin_family = AF_INET;
	server->s_in.sin_port = htons(port);
	server->s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind_server(server))
		return (84);
	return (0);
}

static void loop(all_server_t *all_server, channel_t *chann)
{
	get_client(all_server);
	while (!all_server->error) {
		if (all_server->clients_list) {
			handle_clients(all_server, chann);
		}
	}
}

int	main(int ac, char **av)
{
	all_server_t	all_server;
	channel_t	*channel = NULL;

	all_server.clients_list = NULL;
	all_server.error = 0;
	if (ac != 2 || channel) {
		printf("Error: ./%s port\n", av[0]);
		return (84);
	}
	channel = malloc(sizeof(channel_t));
	if (init_serveur(atoi(av[1]), &all_server.server) || channel == NULL)
		return (84);
	channel->channel = "#general";
	channel->next = NULL;
	loop(&all_server, channel);
	if (close(all_server.server.fd) == -1) {
		printf("Error: close failed\n");
		return (84);
	}
	return (0);
}
