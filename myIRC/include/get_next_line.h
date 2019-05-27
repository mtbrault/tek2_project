/*
** EPITECH PROJECT, 2018
** gnl
** File description:
** gnl
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define BUFF_SIZE	1

struct		s_gnl
{
	char	*st_str;
	int	size;
	int	fd;
	char	*str;
};

char	*strjoin(char const *, char const *);
int	vrf(char *);
char	*erase_leaks(char *, char *);
int	get_next_line(const int fd, char **line);

# define READ_SIZE 1100

#endif /* !GET_NEXT_LINE_H_ */
