NAME = libft.a

SRCS =	ft_atoi.c ft_strlen.c ft_bzero.c ft_calloc.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_printf.c print_char.c print_str.c \
		print_nbr.c print_uns_dec.c print_lowerhex.c \
		print_upperhex.c print_pointer.c exit_error.c print_message.c reset_stats.c \


OBJ = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: $(NAME)

AR = ar -rcs

${NAME}: $(OBJ)
		$(AR) $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: 	fclean $(NAME)

.PHONY: all clean fclean re