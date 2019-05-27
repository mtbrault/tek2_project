/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** philo file
*/

#include <stdio.h>
#include <unistd.h>
#include "philosopher.h"

static void		init(t_philo *this)
{
	if (this->state == EATING) {
		pthread_mutex_lock(this->left);
		lphilo_take_chopstick(this->left);
		pthread_mutex_lock(this->right);
		lphilo_take_chopstick(this->right);
		this->eat -= 1;
		lphilo_eat();
	} else if (this->state == THINKING) {
		pthread_mutex_lock(this->left);
		lphilo_take_chopstick(this->left);
		lphilo_think();
		pthread_mutex_unlock(this->left);
		lphilo_release_chopstick(this->left);
	} else {
		lphilo_sleep();
	}
	this->init = 1;
}

void	*proc(void *data)
{
	t_philo	*this = data;

	if (this == NULL)
		return (NULL);
	init(this);
	while (this->eat) {
		if (this->state == EATING) {
			pthread_mutex_unlock(this->left);
			lphilo_release_chopstick(this->left);
			pthread_mutex_unlock(this->right);
			lphilo_release_chopstick(this->right);
			this->state = SLEEPING;
			lphilo_sleep();
		} else if (this->state == SLEEPING) {
			if (!pthread_mutex_trylock(this->left)) {
				lphilo_take_chopstick(this->left);
				lphilo_think();
				this->state = THINKING;
				pthread_mutex_unlock(this->left);
				lphilo_release_chopstick(this->left);
			}
		} else {
			if (!pthread_mutex_trylock(this->left)) {
				lphilo_take_chopstick(this->left);
				if (!pthread_mutex_trylock(this->right)) {
					lphilo_take_chopstick(this->right);
					this->eat -= 1;
					lphilo_eat();
					this->state = EATING;
				} else {
					pthread_mutex_unlock(this->left);
					lphilo_release_chopstick(this->left);
				}
			}
		}
	}
	pthread_mutex_unlock(this->left);
	lphilo_release_chopstick(this->left);
	pthread_mutex_unlock(this->right);
	lphilo_release_chopstick(this->right);
	pthread_exit(NULL);
}
