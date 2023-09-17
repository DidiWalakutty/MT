# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: diwalaku <diwalaku@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2023/09/16 11:34:07 by diwalaku      #+#    #+#                  #
#    Updated: 2023/09/17 17:55:15 by diwalaku      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell
CC		=	gcc
GFLAGS	=	-Wall -Werror -Wextra
#GFLAGS	+=	-fsanitize=address -g
SRCDIR	= 	src/
OBJDIR	= 	obj/

SRC		= 	client.c server.c \
			utils.c \

SRCOBJ	= $(SRC:%.c=$(OBJDIR)%.o)

LIBFT	=	./libft
HEADERS	=	-I minishell.h -I $(LIBFT)/headers

.PHONY	= all libft clean fclean re

all: libft $(NAME)

$(NAME): $(SRCOBJ)
	$(MAKE) -C $(LIBFT)
	$(CC) $(GFLAGS) $(SRCOBJ) $(LIBFT)/libft.a

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p objfiles
	$(CC) -c $(GFLAGS) -o $@ $<

clean:
	$(MAKE) clean -C $(LIBFT)
	rm -rf obj

fclean: clean
	rm -f minishell
	$(MAKE) fclean -C $(LIBFT)

re: fclean all