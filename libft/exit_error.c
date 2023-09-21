/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/17 18:37:19 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/21 14:21:29 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	exit_error(char *str)
{
	ft_printf("ERROR\n%s\n", str);
	exit(EXIT_FAILURE);
}
