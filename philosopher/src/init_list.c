/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** loop file
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philosopher.h"

static t_philo	*init_list(const int nb_philo, const int nb_eat)
{
	t_philo		*list = malloc(sizeof(t_philo));
	t_philo		*cpy = list;
	pthread_mutex_t	*tmp = NULL;

	if (list == NULL)
		return (NULL);
	for (int i = 0; i < nb_philo; i++) {
		cpy->next = malloc(sizeof(t_philo));
		cpy->right = malloc(sizeof(pthread_mutex_t));
		if (cpy->next == NULL || cpy->right == NULL)
			return (NULL);
		cpy->id = i;
		cpy->eat = nb_eat;
		pthread_mutex_init(cpy->right, NULL);
		cpy->left = tmp;
		tmp = cpy->right;
		if (i % 3 == 0)
			cpy->state = SLEEPING;
		else if (i % 3 == 1)
			cpy->state = THINKING;
		else
			cpy->state = EATING;
		cpy = cpy->next;
	}
	list->left = tmp;
	cpy->next = list;
	return (list);
}

int	loop(const int nb_philo, const int nb_eat)
{
	t_philo	*table = init_list(nb_philo, nb_eat);

	if (table == NULL)
		return (84);
	for (t_philo *parse = table ; parse->next != table &&
		parse->next != NULL ; parse = parse->next) {
		pthread_create(&parse->thread, NULL, proc, parse);
	}
	for (t_philo *parse = table ; parse->next != table &&
		parse->next != NULL; parse = parse->next) {
		pthread_join(parse->thread, NULL);
	}
	return (0);
}
