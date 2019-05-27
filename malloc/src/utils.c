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

void	*split_block(t_block *tmp, size_t s)
{
	t_block	*block;

	block = (t_block *)(tmp->data + s);
	block->size = (tmp->size - s - B_SIZE);
	block->next = tmp->next;
	block->free = 1;
	tmp->size = s;
	tmp->next = block;
}

size_t	padding(size_t size)
{
	return ((((size - 1) / 4) * 4) + 4);
}

t_block	*find_block(t_block *block, size_t s)
{
	t_block	*tmp = glob;

	while (tmp != NULL && !(tmp->free && tmp->size >= s)) {
		*block = *tmp;
		tmp = tmp->next;
	}
	return (tmp);
}
