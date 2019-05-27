/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** listing cmd
*/

#include "serveur.h"

void	users(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	clients_list_t	*tmp;

	(void)chann;
	(void)cmd;
	print_msg("392", get_info(fd, cli), ": UserID\n", fd);
	if (cli->next == NULL)
		print_msg("395", get_info(fd, cli), ": No users\n", fd);
	for (tmp = cli; tmp; tmp = tmp->next) {
		if (strcmp(tmp->name, "*")) {
			print_msg("393", get_info(fd, cli), ":", fd);
			dprintf(fd, "%s\n", tmp->name);
		}
	}
	print_msg("394", get_info(fd, cli), ":End of users\n", fd); 
}

void	list(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	channel_t	*tmp;
	int		count;

	print_msg("321", get_info(fd, cli), "Channel :Users Subject\n", fd);
	for (tmp = chann; tmp; tmp = tmp->next) {
		count = 0;
		if (!cmd[1] || strncmp(tmp->channel, cmd[1], strlen(cmd[1]))) {
			print_msg("322", get_info(fd, cli), tmp->channel, fd);
			for (clients_list_t *c = cli; c; c = c->next) {
				if (!exist_channel(tmp->channel, c->channel))
					count += 1;
			}
			dprintf(fd, " %d :Default\n", count); 
		}
	}
	print_msg("323", get_info(fd, cli), ":End of LIST\n", fd);
}

void	names(clients_list_t *cli, char **cmd, int fd, channel_t *chann)
{
	clients_list_t	*tmp;

	(void)chann;
	if (!cmd[1]) {
		dprintf(fd, "Please select a channel\n");
		return;
	}
	print_msg("353", get_info(fd, cli), "=", fd);
	dprintf(fd, " %s :", cmd[1]);
	for (tmp = cli; tmp; tmp = tmp->next) {
		if (exist_channel(cmd[1], tmp->channel) == 0) {
			dprintf(fd, " %s", tmp->name);
		}
	}
	dprintf(fd, "\n");
	print_msg("366", get_info(fd, cli), cmd[1], fd);
	dprintf(fd, " :End of listing\n");
}
