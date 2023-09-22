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

# Names
NAME_S = server
NAME_C = client
NAME_B_S = server_bonus
NAME_B_C = client_bonus

# Source Files
S_SERVER = server.c
S_CLIENT = client.c
SB_SERVER = ./bonus/server_bonus.c
SB_CLIENT = ./bonus/client_bonus.c

OBJDIR	= obj

# Libraries
LIBFT = libft/libft.a

# Flags & Headers
CFLAGS = -Wall -Wextra -Werror
headers = libft.h
RM = rm -f

# Object Files
OBJ_SERVER = $(addprefix $(OBJDIR)/, $(S_SERVER:.c=.o))
OBJ_CLIENT = $(addprefix $(OBJDIR)/, $(S_CLIENT:.c=.o))
OBJ_B_SERVER = $(addprefix $(OBJDIR)/bonus/, $(notdir $(SB_SERVER:.c=.o)))
OBJ_B_CLIENT = $(addprefix $(OBJDIR)/bonus/, $(notdir $(SB_CLIENT:.c=.o)))

# Object Directory
$(OBJDIR): 
	mkdir -p $(OBJDIR)

$(OBJDIR)/bonus: 
	mkdir -p $(OBJDIR)/bonus

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/bonus/%.o : ./bonus/%.c | $(OBJDIR)/bonus
	$(CC) -c $(CFLAGS) -o $@ $<

# Targets
all: $(NAME_S) $(NAME_C)

bonus: $(NAME_B_S) $(NAME_B_C)

$(NAME_S): $(OBJ_SERVER) $(LIBFT) 
	cc $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_S)

$(NAME_C): $(OBJ_CLIENT) $(LIBFT) 
	cc $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_C)

$(NAME_B_S): $(OBJ_B_SERVER) $(LIBFT)
	cc $(CFLAGS) $(OBJ_B_SERVER) $(LIBFT) -o $(NAME_B_S)

$(NAME_B_C): $(OBJ_B_CLIENT) $(LIBFT)
	cc $(CFLAGS) $(OBJ_B_CLIENT) $(LIBFT) -o $(NAME_B_C)

$(LIBFT):
	make -C libft

# Clean
clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)
	make clean -C libft
	$(RM) -rf $(OBJDIR)
	$(RM) -rf $(OBJDIR)/bonus

fclean: clean
	$(RM) $(NAME_S) $(NAME_C) 
	make fclean -C libft
	$(RM) $(NAME_B_S) $(NAME_B_C)

re: fclean all

.PHONY: all clean fclean
