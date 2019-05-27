/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** header file
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

#include <sys/types.h>
#include <sys/ipc.h>

# define INVALID_NB_ARG		"Invalid number of arguments\n"
# define INVALID_NB_TEAM	"Invalid number of team\n"
# define INVALID_FILE		"Invalid path in first agrument"
# define WIDTH			30
# define HEIGHT			30

typedef struct		lemipc_s
{
	int		msg;
	int		sem;
	int		shm;
	key_t		key;
	int		team;
	int		ai_type;
}			lemipc_t;

int	display_usage();
int	my_puterror(char *);
void	*my_puternull(char *);
int	check_is_int(char *);
int	init_id(lemipc_t*);
int	convert_pos(int, int);
void	display_map(int *);
int	block(int, int);
void	loop(lemipc_t *, int *, int, int);
int	ai(lemipc_t *, int *, int);
int	is_alone(int *, lemipc_t *);
int	map_is_full(int *);
int	is_alive(int *, int, lemipc_t *);
int	die_middle(lemipc_t *, int *, int);

#endif /* !LEMIPC_H_ */
