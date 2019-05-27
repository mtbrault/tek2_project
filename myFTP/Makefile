##
## EPITECH PROJECT, 2018
## strace
## File description:
## makefile
##

CC	=	gcc

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I./include/

NAME	=	server

SRCS	=	src/main.c		\
		src/tools.c		\
		src/init.c		\
		src/wordtab.c		\
		src/loop.c		\
		src/reply_code.c	\
		src/file_action.c	\
		src/file_action2.c	\
		src/login.c		\
		src/tools2.c		\
		src/pasv.c		\
		src/stor.c

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
