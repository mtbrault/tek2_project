/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** client header
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "get_next_line.h"

int	my_perror(char *, int);
char	**my_str_to_wordtab(char *, char);
int	handle_message(int);
int	connect_serv(char *, int);
int	create_socket_by_name(char *);

#endif /* !CLIENT_H_ */
