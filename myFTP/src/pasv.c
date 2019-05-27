/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** pasv
*/

#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include "myftp.h"

void	port(ftp_t *ftp, char **cmd)
{
	if (!cmd[1] || cmd[2] || check_is_num(cmd[1]) == 1)
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else {
		print_msg(200, ftp->client_fd);
	}
}

void	noop(ftp_t *ftp, char **cmd)
{
	if (cmd[1])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else
		print_msg(200, ftp->client_fd);
}

static int	generate_port(ftp_t *ftp)
{
	int			rand = (random() % 40000) + 1001;
	struct protoent		*pe;
	struct sockaddr_in	sin;
	int			size = sizeof(sin);

	pe = getprotobyname(TCP);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(rand);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (pe == NULL)
		return (1);
	ftp->pasv_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (ftp->pasv_fd == -1)
		return (1);
	else if (bind(ftp->pasv_fd, (struct sockaddr *)&sin, size) == -1)
		return (1);
	else if (listen(ftp->pasv_fd, 4200) == -1)
		return (1);
	return (rand);
}

void	pasv(ftp_t *ftp, char **cmd)
{
	char			*ip;
	int			port;
	char			**ip_tab;

	if (cmd[1])
		print_msg(504, ftp->client_fd);
	else if (ftp->user == 0 || ftp->pass == 0)
		print_msg(530, ftp->client_fd);
	else {
		ip = inet_ntoa(ftp->client_sin.sin_addr);
		port = generate_port(ftp);
		if (port == 1)
			return (print_msg(451, ftp->client_fd));
		ftp->mode = 1;
		print_msg(227, ftp->client_fd);
		ip_tab = my_str_to_wordtab(ip, '.');
		for (int i = 0; ip_tab[i] != NULL; i++)
			dprintf(ftp->client_fd, "%s,", ip_tab[i]);
		dprintf(ftp->client_fd, "%d,%d).\n", port / 256, port % 256);
	}
}
