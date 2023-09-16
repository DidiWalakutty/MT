# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: diwalaku <diwalaku@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2023/09/16 11:34:07 by diwalaku      #+#    #+#                  #
#    Updated: 2023/09/16 15:55:53 by diwalaku      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell
CC		=	gcc
GFLAGS	=	-Wall -Werror -Wextra
#GFLAGS	+=	-fsanitize=address -g
SRCDIR	= src/
OBJDIR	= obj/

SRC		= 	client.c server.c \
			utils.c \

SRCOBJ	= $(SRC:%.c=$(OBJDIR)%.o)

.PHONY	= all clean fclean re

# all:

$(NAME): $(SRCOBJ)
	$(MAKE) -C
	$(CC) $(GFLAGS) $(SRCOBJ)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p objfiles
	$(CC) -c $(GFLAGS) -o $@ $<

clean:
	rm -rf obj
#	$(MAKE) clean -C $()

fclean: clean
	rm -f minishell

re: fclean #all