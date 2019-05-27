/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** client.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

typedef struct protoent t_proto;

int	my_perror(char *msg, int sig)
{
	dprintf(2, "%s\n", msg);
	return (sig);
}

int	create_socket_by_name(char *name)
{
	t_proto	*proto;
	int	sockfd;

	proto = getprotobyname(name);
	if (!proto)
		return (my_perror("Error protobyname", 1));
	sockfd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (sockfd == -1)
		return (my_perror("Error when creating socket", 1));
	return (sockfd);
}

static int	loop2(char *buff)
{
	char	**tab = my_str_to_wordtab(buff, ' ');

	tab = my_str_to_wordtab(tab[1], ':');
	if (tab == NULL || !tab[1]) {
		printf("Arguments expected\n");
		return (-1);
	}
	return (connect_serv(tab[0], (tab[1]) ? atoi(tab[1]) : 6667));
}

static int	loop(void)
{
	int	loop = 0;
	char	*buff;
	int	sockfd;

	while (loop == 0) {
		get_next_line(0, &buff);
		if (buff == NULL)
			return (0);
		if (strncmp(buff, "/server", 7) != 0) {
			printf("Please connect to a server with /server\n");
			continue;
		}
		sockfd = loop2(buff);
		if (sockfd != -1)
			loop = 1;
	}
	return (handle_message(sockfd));
}

int	main(int ac, char **av)
{
	int	ret = 0;

	(void)av;
	if (ac != 1)
		return (my_perror("No arguments excpected", 84));
	ret = loop();
	return (ret);
}
