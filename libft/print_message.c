/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 22:20:49 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/23 19:38:08 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*print_message(char *message)
{
	ft_printf("%s\n", message);
	free(message);
	return (NULL);
}
