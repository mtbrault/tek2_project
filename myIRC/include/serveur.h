/*
** EPITECH PROJECT, 2018
** serveur
** File description:
** serveur
*/

#ifndef SERVEUR_H_
# define SERVEUR_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

# define CMD_SIZE	8

typedef struct			channel_s
{
	char			*channel;
	struct channel_s	*next;
}				channel_t;

typedef struct clients_list_s
{
        channel_t		*channel;
	int			fd;
	char			*name;
	int			find;
	struct clients_list_s	*next;
	struct clients_list_s	*last;
}	clients_list_t;

typedef struct	cmd_s
{
	char	*cmd;
	void	(*func)(clients_list_t *, char **, int, channel_t *);
}		cmd_t;

typedef struct	server_s
{
	struct	protoent	*pe;
	int			fd;
	struct sockaddr_in	s_in;
	struct sockaddr_in	s_in_client;
	socklen_t		s_in_size;
}		server_t;

typedef struct	all_server_s
{
	int		client_fd;
	fd_set		readfds;
	int		error;
	clients_list_t	*clients_list;
	clients_list_t	*tmp;
	server_t	server;
}		all_server_t;

clients_list_t	*add_client(clients_list_t *clients_list, int fd);
clients_list_t	*add_client2(clients_list_t *, int);
int		check_function(int, clients_list_t **, char **, channel_t *);
void		get_client(all_server_t *all_server);
char		*get_info(int, clients_list_t *);
char		**my_str_to_wordtab(char *, char);
int		handle_clients(all_server_t *all_server, channel_t *);
void		launch_client(all_server_t *, channel_t *);
void		free_tab(char **);
void		nick(clients_list_t *, char **, int, channel_t *);
void		list(clients_list_t *, char **, int, channel_t *);
void		join(clients_list_t *, char **, int, channel_t *);
void		part(clients_list_t *, char **, int, channel_t *);
void		users(clients_list_t *, char **, int, channel_t *);
void		user(clients_list_t *, char **, int, channel_t *);
void		names(clients_list_t *, char **, int, channel_t *);
void		msg(clients_list_t *, char **, int, channel_t *);
void		del_elem_from_list(int, clients_list_t **);
void		quit(clients_list_t **, char **, int);
int		send_msg(int, clients_list_t *, char **, char *);
int		exist_channel(char *, channel_t *);
void		print_msg(char *, char *, char *, int);

#endif /* !SERVEUR_H_ */
