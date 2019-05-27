/*
** EPITECH PROJECT, 2018
** PSU_2017_Malloc
** File description:
** Main file
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

void	show_alloc_mem(void)
{
	t_block	*block;

	block = glob;
	printf(PRINT_BREAK, sbrk(0));
	if (block == NULL)
		printf(MEMORY_FAIL);
	while (block) {
		if (block->free == 0)
			printf(PRINT_ALLOC, &block->data,
			       &block->data + block->size, block->size);
		block = block->next;
	}
}

t_block	*memory_alloc(t_block *end, size_t s)
{
	t_block	*tmp;

	tmp = sbrk(0);
	if (sbrk(B_SIZE + s) == ((void *) -1)) {
		dprintf(2, "%s", SBRK_FAIL);
		return (NULL);
	}
	tmp->size = s;
	tmp->next = NULL;
	tmp->free = 0;
	return (tmp);
}

void	*malloc(size_t size)
{
	t_block	*block = NULL;
	t_block	*tmp = NULL;
	size_t	s = padding(size);

	pthread_mutex_lock(&mutex);
	if (glob == NULL) {
		tmp = glob;
		block = alloc_glob(block, tmp, s);
	} else {
		block = alloc_isglob(block, s);
	}
	if (block == NULL)
		return (NULL);
	glob = block;
	pthread_mutex_unlock(&mutex);
	return (block->data);
}
