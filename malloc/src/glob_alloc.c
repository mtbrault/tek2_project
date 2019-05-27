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

t_block	*alloc_glob(t_block *block, t_block *tmp, size_t s)
{
	block = find_block(tmp, s);
	if (block != NULL) {
		if ((block->size - s) >= (B_SIZE + NBR_S))
			split_block(block, s);
		block->free = 0;
	} else {
		block = memory_alloc(tmp, s);
		if (block == NULL) {
			dprintf(2, "%s", MALLOC_FAIL);
			return (NULL);
		}
	}
	return (block);
}

t_block *alloc_isglob(t_block *block, size_t s)
{
	block = memory_alloc(NULL, s);
	if (block == NULL) {
		dprintf(2, "%s", MALLOC_FAIL);
		return (NULL);
	}
	return (block);
}
