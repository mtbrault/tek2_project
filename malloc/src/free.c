/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** free function
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

t_block	*tmp_fusion(t_block *tmp)
{
	tmp->size = (tmp->size + B_SIZE) + (tmp->next->size);
	tmp->next = tmp->next->next;
	return (tmp);
}

t_block	*fusion(t_block *tmp)
{
	if (tmp->next->free)
		if (tmp->next != NULL) {
			tmp = tmp_fusion(tmp);
			if (tmp->next)
				tmp->next->prev = tmp;
		}
	return (tmp);
}

t_block	*setusable(t_block *block, void *ptr)
{
	block = get_address(ptr);
	block->free = 1;
	return (block);
}

void	fusion_exec(t_block *blk)
{
	if (blk->next)
		fusion(blk);
	else {
		if (blk->prev)
			blk->prev->next = NULL;
		else
			glob = NULL;
		brk(blk);
	}	
}

void	free(void *ptr)
{
	t_block	*blk = NULL;

	if (verif_address(ptr) != 0) {
		blk = setusable(blk, ptr);
		if (blk->prev->free && blk->prev)
			blk = fusion(blk->prev);
		fusion_exec(blk);
	}
}
