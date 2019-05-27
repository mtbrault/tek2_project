##
## EPITECH PROJECT, 2018
## strace
## File description:
## makefile
##

CC	=	gcc -g3

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I./include/

NAME	=	strace

SRCS	=	src/main.c		\
		src/start_strace.c	\
		src/tools.c		\
		src/display_type.c	\
		src/display_strace.c

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
