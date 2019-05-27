##
## EPITECH PROJECT, 2018
## nm_objdump
## File description:
## makefile
##

CC	= gcc

RM	= rm -f

SRC1	= 	server_src/main.c		\
		server_src/handle_clients.c 	\
		server_src/listing_cmd.c	\
		server_src/quit.c		\
		server_src/wordtab.c		\
		server_src/tools.c		\
		server_src/get_next_line.c	\
		server_src/get_next_line2.c	\
		server_src/join.c		\
		server_src/part.c		\
		server_src/privmsg.c		\
		server_src/nick.c		\
		server_src/init.c

SRC2	=	client_src/client.c		\
		client_src/cmd.c		\
		server_src/get_next_line.c	\
		server_src/get_next_line2.c	\
		server_src/wordtab.c

NAME1	= server

NAME2	= client

CFLAGS	+= -I./include
CFLAGS	+= -Wall -Wextra -Werror

OBJS1	= $(SRC1:.c=.o)

OBJS2	= $(SRC2:.c=.o)

all:	server client

server:	 $(OBJS1)
	 $(CC) $(OBJS1) -o $(NAME1) $(CFLAGS)

client: $(OBJS2)
	 $(CC) $(OBJS2) -o $(NAME2) $(CFLAGS)

clean:
	$(RM) $(OBJS1)
	$(RM) $(OBJS2)

fclean: clean
	$(RM) $(NAME1)
	$(RM) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
