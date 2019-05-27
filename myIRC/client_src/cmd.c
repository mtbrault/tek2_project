/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** cmd handling
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"

typedef struct sockaddr_in t_addr;

int	connect_serv(char *ip, int port)
{
	t_addr	s_in;
	int	sockfd;

	(void)ip;
	sockfd = create_socket_by_name("TCP");
	if (sockfd == 1)
		return (my_perror("Error when creating new socket", -1));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (connect(sockfd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
		return (my_perror("Error when connecting", -1));
	return (sockfd);
}

static int	message_handling(char *cmd, int sockfd)
{
	char	*new;
	int	i;

	if (!strncmp("/msg", cmd, 4)) {
		new = malloc(sizeof(char) * (strlen(cmd) + 4));
		new[0] = 'P';
		new[1] = 'R';
		new[2] = 'I';
		new[3] = 'V';
		new[4] = 'M';
		new[5] = 'S';
		new[6] = 'G';
		for (i = 7; cmd[i - 3] != '\0'; i++)
			new[i] = cmd[i - 3];
		new[i] = '\0';
		printf("%s\n", new);
		dprintf(sockfd, "%s\n", new);
		free(new);
	}
	return (sockfd);
}

static int	cmd_handling(char *cmd, int sockfd)
{
	char	**tab;

	if (cmd == NULL)
		return (dprintf(sockfd, "QUIT Socket closed\n") * 0 + 1);
	if (!strncmp("/msg", cmd, 4))
		return (message_handling(cmd, sockfd));
	else if (!strncmp("/server", cmd, 7)) {
		close(sockfd);
		tab = my_str_to_wordtab(my_str_to_wordtab(cmd, ' ')[0], ':');
		return (connect_serv(tab[0], (tab[1]) ? atoi(tab[1]) : 6667));
	}
	for (int i = 0; cmd[i] != '\0' && cmd[i] != ' '; i++) {
		if (cmd[i] == '/')
			cmd[i] = ' ';
		else if (cmd[i] >= 'a' && cmd[i] <= 'z')
			cmd[i] -= 32;
	}
	dprintf(sockfd, "%s\n", cmd);
	return (sockfd);
}

static int	fd_handling(int sockfd, fd_set readfds)
{
	char	buff[140];
	char	*new;

	if (FD_ISSET(sockfd, &readfds)) {
		bzero(buff, 140);
		read(sockfd, buff, 100);
		printf("%s", buff);
	}
	if (FD_ISSET(0, &readfds)) {
		get_next_line(0, &new);
		sockfd = cmd_handling(new, sockfd);
		if (sockfd == 1)
			return (1);
	}
	return (0);
}

int handle_message(int sockfd)
{
	fd_set	readfds;

	if (sockfd == -1)
		return (84);
	while (sockfd >= 0) {
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		FD_SET(sockfd, &readfds);
		if (select(sockfd + 1, &readfds, NULL, NULL, NULL) == -1)
			return (-1);
		if (fd_handling(sockfd, readfds) == 1)
			return (0);
	}
	return (0);
}
