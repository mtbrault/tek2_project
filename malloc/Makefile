##
## EPITECH PROJECT, 2018
## PSU_2017_malloc
## File description:
## makefile
##

CC	= gcc

RM	= rm -f

SRC	= src/malloc.c		\
	  src/utils.c 		\
	  src/free.c 		\
	  src/glob_alloc.c	\
	  src/realloc.c

NAME	= libmy_malloc.so

CFLAGS	+= -I./include
CFLAGS	+= -W -Wextra -Werror -fpic

OBJS	= $(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
