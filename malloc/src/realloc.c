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

t_block	*get_address(void *ptr)
{
	char	*addr;

	addr = ptr;
	addr = addr - B_SIZE;
	ptr = addr;
	return (ptr);
}

int	verif_address(void *ptr)
{
	int	res = 0;

	if (glob) {
		if (ptr < sbrk(0) && ptr > glob)
			return (ptr == (get_address(ptr))->ptr);
		else
			return (res);
	}
	return (res);
}

void	*realloc(void *ptr, size_t size)
{
	t_block *blk;
	void	*mem;

	if (size <= 0) {
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ptr = malloc(size));
	if (verif_address(ptr)) {
		blk = get_address(ptr);
		if (blk->size >= size)
			return ptr;
	}
	mem = malloc(size);
	memcpy(mem, ptr, size);
	free(ptr);
	return (mem);
}

void	*calloc(size_t n, size_t size)
{
	size_t	total = n * size;
	void	*p = malloc(total);

	if (!p)
		return (NULL);
	return memset(p, 0, total);
}
