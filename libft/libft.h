/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 18:27:25 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/27 20:38:58 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

//	libft
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// printf
int		ft_printf(const char *format, ...);
int		print_char(char c);
int		print_str(char *s);
int		print_nbr(int n);
int		print_uns_dec(unsigned int n);
int		print_lowerhex(unsigned long n);
int		print_upperhex(unsigned int n);
int		print_pointer(unsigned long ptr);

// other
void	exit_error(char *str);
void	*print_message(char *message);
void	reset_stats(int *bit, char *c);

#endif