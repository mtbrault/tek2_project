/*
** EPITECH PROJECT, 2018
** strace
** File description:
** strace header
*/

#ifndef STRACE_H_
# define STRACE_H_

#include <sys/user.h>

# define BAD_PID	"Bad PID\n"
# define BAD_NB_ARGS	"Invalid number of arguments\n"
# define BAD_FORK	"Problem during fork\n"
# define CANT_TRACE	"Program can't be traced\n"
# define CANT_EXEC	"Problem during execution of the program\n"
# define TAB_SIZE	3

int	is_number(char *);
int	my_puterror(char *);
int	launch_program(char **, char **, int);
int	start_strace(int, int);
void	disp_string(unsigned long long int reg, int pid);
void	print_return_value(struct user_regs_struct *, int, int);
void	print_arg(int, unsigned long long, int, int);
void	disp_string(unsigned long long int, int);
void	disp_num(unsigned long long int, int);
void	disp_unsigned_num(unsigned long long int, int);

typedef struct	syscall_s
{
	int	num;
	char	*name;
	int	nb_args;
	int	return_type;
	int	a1;
	int	a2;
	int	a3;
	int	a4;
	int	a5;
	int	a6;
}		syscall_t;

typedef struct	struct_s
{
	void	(*function)(unsigned long long int, int);
	int	type;
}		struct_t;

#endif /* !STRACE_H_ */
