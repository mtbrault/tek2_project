/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** header file
*/

#ifndef MYFTP_H_
# define MYFTP_H_

#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

# define REPLY_SIZE	22
# define CMD_SIZE	14
# define MALLOC		"Malloc failed\n"
# define BAD_NB_ARG	"Invalid number of argument\n"
# define BAD_PORT	"Invalid port\n"
# define BAD_PATH	"Invalid path\n"
# define TCP		"TCP"
# define FAIL_PROT	"Fail to load protocol\n"
# define FAIL_SOCKET	"Fail to load sockets\n"
# define FAIL_BIND	"Fail to bind\n"
# define FAIL_LISTEN	"Fail to listen\n"

typedef struct			reply_s
{
	int			code;
	char			*message;
}				reply_t;

typedef struct			ftp_s
{
	int			server_fd;
	int			client_fd;
	struct sockaddr_in	server_sin;
	struct sockaddr_in	client_sin;
	int			user;
	int			mode;
	int			pass;
	char			*home;
	char			*ip;
	int			pasv_fd;
}				ftp_t;

typedef struct	cmd_s
{
	char	*cmd;
	void    (*func)(ftp_t *, char **);
}		cmd_t;

int	my_puterror(char *, ftp_t *);
int	error_handling(int, char **, ftp_t *);
int	check_is_num(char *);
int	init_server(ftp_t *, int);
int	loop(ftp_t *);
void	user(ftp_t *, char **);
void	pass(ftp_t *, char **);
void	cwd(ftp_t *, char **);
void	cdup(ftp_t *, char **);
void	dele(ftp_t *, char **);
void	pwd(ftp_t *, char **);
void	pasv(ftp_t *, char **);
void	port(ftp_t *, char **);
void	help(ftp_t *, char **);
void	noop(ftp_t *, char **);
void	retr(ftp_t *, char **);
void	stor(ftp_t *, char **);
void	list(ftp_t *, char **);
void	quit(ftp_t *, char **);
char	**my_str_to_wordtab(char *, char);
void	free_tab(char **);
void	my_upper(char *);
void	print_msg(int, int);
int	my_strcmp(char *, char *);
char	*get_pwd(char *);
void	read_dir(DIR *, int);

#endif /* !MYFTP_H_ */
