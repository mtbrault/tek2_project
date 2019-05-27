/*
** EPITECH PROJECT, 2018
** myIRC
** File description:
** wordtab
*/

#include <unistd.h>
#include <stdlib.h>

void	free_tab(char **tab)
{
	for (int i = 0; tab[i] != NULL; i++)
		free(tab[i]);
	free(tab);
}

static char	**size_str_tab(char *str, char **tab, int len, char c)
{
	int	i = 0;
	int	k;
	int	j = 0;

	while (i < len) {
		k = 0;
		while (str[j] != c && str[j] != '\0') {
			j = j + 1;
			k = k + 1;
		}
		while (str[j] == c && str[j] != '\0') {
			j = j + 1;
		}
		tab[i] = malloc(sizeof(char) * k + 2);
		if (tab[i] == NULL)
			return (NULL);
		i = i + 1;;
	}
	return (tab);
}

static char	**cpy_cara_str_tab(char *str, char **tab, int len, char c)
{
	int	i = 0;
	int	j = 0;
	int	k;

	while (i < len) {
		k = 0;
		while (str[j] == c && str[j] != '\0')
			j = j + 1;
		while ((str[j] != c && str[j] != '\0')) {
			tab[i][k] = str[j];
			k = k + 1;
			j = j + 1;
		}
		tab[i][k] = '\0';
		i = i + 1;
	}
	while (tab[i - 1][0] == '\0')
		i = i - 1;
	tab[i] = NULL;
	return (tab);
}

char	**my_str_to_wordtab(char *str, char c)
{
	char	**tab;
	int	i = 1;
	int	len = 1;

	if (str == NULL)
		return (NULL);
	if (str[0] == '\0')
		return (NULL);
	while (str[i]) {
		if (str[i] != c && str[i - 1] == c && str[i] != '\0')
			len = len + 1;
		i = i + 1;
	}
	tab = malloc(sizeof(char *) * (len + 1));
	if (tab == NULL || !(tab = size_str_tab(str, tab, len, c)))
		return (NULL);
	tab = cpy_cara_str_tab(str, tab, len, c);
	return (tab);
}
