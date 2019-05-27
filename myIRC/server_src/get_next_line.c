/*
** EPITECH PROJECT, 2018
** header
** File description:
** header
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*strjoin(char const *s1, char const *s2)
{
	int	x;
	int	len_s1;
	int	len_s2;
	char	*str;

	x = 0;
	if (s1 && s2) {
		len_s1 = strlen(s1);
		len_s2 = strlen(s2);
		if (!(str = (char *)malloc(sizeof(char*) *
					(len_s1 + len_s2 + 1))))
			return (0);
		while (x < len_s1)
			str[x++] = *s1++;
		while (x < len_s1 + len_s2)
			str[x++] = *s2++;
		str[x] = '\0';
		return (str);
	}
	return (NULL);
}

int	s(char *st_str, int ret, char *str, char **line)
{
	int	i;
	char	*tmp;

	i = 0;
	++ret;
	tmp = strjoin(str, st_str);
	tmp[vrf(tmp)] = '\0';
	while (st_str[ret] != '\0')
		st_str[i++] = st_str[ret++];
	st_str[i] = '\0';
	if ((*line = strdup(tmp)) == NULL)
		return (-1);
	free(str);
	free(tmp);
	return (1);
}

static char	*strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(*str) * size + 1)))
		return (0);
	str[size] = '\0';
	while (size > 0)
		str[size-- - 1] = '\0';
	return (str);
}

static int	check_return(struct s_gnl gnl[1095], int fd, char **line)
{
	if (gnl[fd].size == -1)
		return (-1);
	if (gnl[fd].size == 0 && (strlen(gnl[fd].st_str) == 0))
		return (0);
	gnl[fd].st_str = strnew(1);
	if (!(*line = strdup(gnl[fd].str)))
		return (-1);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static struct s_gnl	gnl[1095];

	if (BUFF_SIZE < 1 || !line || fd < 0)
		return (-1);
	if (gnl[fd].st_str == NULL)
		gnl[fd].st_str = strnew(BUFF_SIZE);
	gnl[fd].str = strdup(gnl[fd].st_str);
	if (vrf(gnl[fd].str) != -1)
		return (s(gnl[fd].st_str, vrf(gnl[fd].st_str),
			gnl[fd].str, line));
	while ((gnl[fd].size = read(fd, gnl[fd].st_str, BUFF_SIZE)) > 0) {
		gnl[fd].st_str[gnl[fd].size] = '\0';
		if (vrf(gnl[fd].st_str) != -1)
			return (s(gnl[fd].st_str, vrf(gnl[fd].st_str),
				gnl[fd].str, line));
		gnl[fd].str = erase_leaks(gnl[fd].str, gnl[fd].st_str);
	}
	return (check_return(gnl, fd, line));
}
