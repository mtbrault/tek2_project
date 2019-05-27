##
## EPITECH PROJECT, 2018
## philosopher
## File description:
## makefile
##

CC	=	gcc

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I./include/

LDFLAGS =	-L./lib -lriceferee -lpthread

NAME	=	philo

SRCS	=	src/main.c	\
		src/philo.c	\
		src/init_list.c

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
