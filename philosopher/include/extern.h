/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** extern lib
*/

#ifndef EXTERN_H_
# define EXTERN_H_

#include <pthread.h>

int	RCFStartup(int ac, char **av);
void	RCFCleanup(void);
int	lphilo_eat(void);
int	lphilo_sleep(void);
int	lphilo_think(void);
int	lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
int	lphilo_release_chopstick(const pthread_mutex_t *mutex_id);

#endif /* EXTERN_H_ */
