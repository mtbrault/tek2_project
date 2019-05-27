/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** init
*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "myftp.h"

char	*get_pwd(char *str)
{
	int	i;
	int	s;
	char	*new;

	for (i = 0; str[i] != '\0'; i++);
	i -= 2;
	for (s = i; str[s] != '/' && s > 0; s--);
	new = malloc(sizeof(char) * (i - s));
	if (new == NULL)
		return (NULL);
	i = 0;
	s++;
	while (str[s] != '\0') {
		new[i] = str[s];
		i += 1;
		s += 1;
	}
	new[i] = '\0';
	return (new);
}

int	init_server(ftp_t *ftp, int port)
{
	struct protoent	*pe;
	int		size = sizeof(ftp->server_sin);
	struct sockaddr	*tmp = (struct sockaddr *)&ftp->server_sin;

	pe = getprotobyname(TCP);
	ftp->server_sin.sin_family = AF_INET;
	ftp->server_sin.sin_port = htons(port);
	ftp->server_sin.sin_addr.s_addr = INADDR_ANY;
	if (pe == NULL)
		return (my_puterror(FAIL_PROT, ftp));
	ftp->server_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (ftp->server_fd == -1)
		return (my_puterror(FAIL_SOCKET, ftp));
	else if (bind(ftp->server_fd, tmp, size) == -1)
		return (my_puterror(FAIL_BIND, ftp));
	else if (listen(ftp->server_fd, 4200) == -1)
		return (my_puterror(FAIL_LISTEN, ftp));
	return (0);
}
