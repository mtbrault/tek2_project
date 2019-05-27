/*
** EPITECH PROJECT, 2018
** PSU_2017_Malloc
** File description:
** Main file
*/

#ifndef MALLOC_H_
# define MALLOC_H_

#include <pthread.h>
#include <stdlib.h>

/*  *************************** **
**          MACRO               **
**  *************************** */

# define SBRK_FAIL	"Memory full , mem canno't be allocated\n"
# define BAD_SIZE	"Size must be higher than 0"
# define PRINT_ALLOC	"%p - %p : %zu bytes\n"
# define PRINT_BREAK	"break: %p\n"
# define MEMORY_FAIL	"No memory available\n"
# define MALLOC_FAIL	"Malloc failed\n"
# define B_SIZE		sizeof(struct s_block)
# define NBR_S		4

static void	*glob = NULL;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*  *************************** **
**            LIST              **
**  *************************** */

typedef struct	s_block
{
	size_t		size;
	struct s_block	*next;
	struct s_block	*prev;
	void		*ptr;
	int		free;
	char		data[1];
}		t_block;

/*  *************************** **
**          PROTOTYPE           **
**  *************************** */

void	*realloc(void *, size_t);
void	free(void *);
t_block	*memory_alloc(t_block *, size_t);
void	*split_block(t_block *, size_t);
t_block	*find_block(t_block *, size_t);
void	show_alloc_mem(void);
t_block	*get_address(void *);
int	verif_address(void *);
size_t	padding(size_t);
t_block	*alloc_glob(t_block *, t_block *, size_t);
t_block	*alloc_isglob(t_block *, size_t);

#endif /* !MALLOC_H_ */
