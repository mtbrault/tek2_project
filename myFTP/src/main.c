/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** main file
*/

#include <unistd.h>
#include <stdlib.h>
#include "myftp.h"

int	main(int ac, char **av)
{
	ftp_t		*ftp = malloc(sizeof(ftp_t));
	int		ret = 0;

	if (ftp == NULL || error_handling(ac, av, ftp) == 84)
		return (84);
	else if (init_server(ftp, atoi(av[1])) == 84)
		return (84);
	ret = loop(ftp);
	if (ret == 84)
		return (84);
	free(ftp);
	close(ftp->server_fd);
	close(ftp->client_fd);
	return (0);
}
