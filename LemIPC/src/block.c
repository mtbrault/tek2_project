/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** lock
*/

#include <sys/sem.h>

void	block(int id, int opt)
{
	struct sembuf	occup;

	occup.sem_num = 0;
	occup.sem_flg = 0;
	occup.sem_op = (opt == 1) ? -1 : 1;
	semop(id, &occup, 1);
}
