##
## EPITECH PROJECT, 2018
## lemipc
## File description:
## makefile
##

CC	=	gcc

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I./include/

NAME	=	lemipc

SRCS	=	src/main.c		\
		src/tools.c		\
		src/init_game.c		\
		src/display_map.c	\
		src/block.c		\
		src/loop.c		\
		src/ai.c		\
		src/checking.c 		\
		src/die_middle.c	\
		src/alive.c

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
