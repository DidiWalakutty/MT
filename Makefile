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

NAME = minitalk
OBJDIR	= mini_obj

SERVER = server.c
CLIENT = client.c

NSERVER = server
NCLIENT = client

RM = rm -f

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

headers = libft.h

OSERVER = $(SERVER:.c=.o)
OCLIENT = $(CLIENT:.c=.o)

all: $(NSERVER) $(NCLIENT)

$(OBJDIR): 
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(NSERVER): $(OBJDIR) $(OSERVER) $(LIBFT)
	cc $(CFLAGS) $(SERVER) $(LIBFT) -o $(NSERVER)

$(NCLIENT): $(OBJDIR) $(OCLIENT) $(LIBFT)
	cc $(CFLAGS) $(CLIENT) $(LIBFT) -o $(NCLIENT)

$(LIBFT):
	make -C libft

clean:
	$(RM) $(OSERVER) $(OCLIENT)
	make clean -C libft

fclean: clean
	$(RM) $(NSERVER) $(NCLIENT)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean