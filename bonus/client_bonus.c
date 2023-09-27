/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 15:48:12 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/27 20:32:58 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_receiver = 0;

static void	send_character(char c, int pid)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		c >>= 1;
		shift++;
	}
	usleep(200);
}

static void	send_string(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_character(str[i++], pid);
	}
	send_character('\0', pid);
	kill(pid, SIGUSR1);
}

// Printing every signal that's received is
// probably overkill for the bonus.
static void	delivered(int sig)
{
	if (sig == g_receiver)
		g_receiver = 1;
	else
		g_receiver = 0;
	ft_printf("signal received\n");
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	pid = ft_atoi(argv[1]);
	if (argc != 3)
		exit_error("Client: Wrong amount of arguments");
	else if (kill(pid, 0) < 0)
		exit_error("Client: given PID is not valid");
	signal(SIGUSR1, delivered);
	signal(SIGUSR2, delivered);
	send_string(argv[2], pid);
	ft_printf("Message delivered.\n");
	return (0);
}
