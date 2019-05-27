/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** header
*/

#ifndef PHILOSOPHER_H_
# define PHILOSOPHER_H_

#include "extern.h"

typedef enum 	state_e
{
	EATING,
	SLEEPING,
	THINKING
}	        state_e;

typedef struct			s_philo
{
	size_t			id;
	size_t			eat;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_t 		thread;
	state_e			state;
	char			init;
	struct s_philo		*next;
	
}				t_philo;

int	loop(int, int);
void	*proc(void *);

#endif /* !PHILOSOPHER_H_ */
