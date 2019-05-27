/*
** EPITECH PROJECT, 2018
** strace
** File description:
** start_strace file
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>
#include "syscall.h"

static void	fill_type(int *type, struct user_regs_struct *r)
{
	type[0] = table[r->rax].a1;
	type[1] = table[r->rax].a2;
	type[2] = table[r->rax].a3;
	type[3] = table[r->rax].a4;
	type[4] = table[r->rax].a5;
	type[5] = table[r->rax].a6;
}

static long	do_peektext(int pid, struct user_regs_struct *regs)
{
	return (ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL));
}

static void	catch_syscall(int pid, struct user_regs_struct *regs,
			int is_s)
{
	long			val = do_peektext(pid, regs);
	unsigned char		f = (unsigned)0xFF & val;
	unsigned char		s = ((unsigned)0xFF00 & val) >> 8;
	unsigned long long int	r_val[6] = {regs->rdi, regs->rsi, regs->rdx,
					regs->r10, regs->r8, regs->r9};
	int			type[6];

	if ((f == 0xCD && s == 0x80) || (f == 0x0F && s == 0x05)) {
		fill_type(type, regs);
		dprintf(2, "%s(", table[regs->rax].name);
		for (int i = 0; i < table[regs->rax].nb_args; i++) {
			print_arg(is_s, r_val[i], type[i], pid);
			if ((i + 1) < table[regs->rax].nb_args)
				dprintf(2, ", ");
		}
		dprintf(2, ") = ");
		print_return_value(regs, pid, is_s);
	}
}

int	start_strace(int pid, int is_s)
{
	int			status;
	int			loop = 0;
	struct rusage		rusage;
	struct user_regs_struct	regs;

	while (loop == 0) {
		ptrace(PTRACE_GETREGS, pid, NULL, &regs);
		ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
		wait4(pid, &status, 0, &rusage);
		if (WEXITSTATUS(status) == 84)
			return (84);
		if (WIFSTOPPED(status))
			catch_syscall(pid, &regs, is_s);
		else if (WIFEXITED(status))
			loop = 1;
	}
	dprintf(2, "+++ exited with %d +++\n", WEXITSTATUS(status));
	return (0);
}

int	launch_program(char **av, char **env, int is_s)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (my_puterror(BAD_FORK));
	else if (pid == 0) {
		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
			exit(my_puterror(CANT_TRACE));
		else if (execve(av[0], av, env) == -1) {
			exit(my_puterror(CANT_EXEC));
		}
		exit(0);
	}
	else
		return (start_strace(pid, is_s));
}
