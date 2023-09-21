/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 15:48:12 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/17 22:15:02 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// !!! bonus should be in a different file !!!
// static void	received_signal(int signal)
// {
// 	if (signal == SIGUSR1)
// 	{
// 		ft_printf("Received signal\n");
// 		exit(0);
// 	}
// }

// SIGUSR1 = 1
// SIGUSR2 = 0
// C &(1 << shift): shift left operator: moves the bits to the left, 
// and discards the far left bit.
// usleep: delay without relying on a signal.
static void	send_character(char c, int pid)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if (c & 1 )
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		shift++;
		usleep(100);
	}
}

// static void	send_string(char *str, int pid)
// {
// 	int	i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		send_character(str[i++], pid);
// 	}
// 	send_character('\0', pid);
// }

// Client sends the character to the server.
// Kill notifies server that a signal was send.

// Not only does the the PID have to be digits, it also 
// has to be a running process. // The 'else if' checks if 
// there's a running process with the given number from argv[1].
// 1st 0: The 0 behind it states you don't want to send a message 
// or signal a process, just check if argv[1] exists.
// 2nd 0: If the answer is < 0, it means there was a problem, 
// like no digits or no existing process.
// If it's 0 or > 0 a process with the specified PID exists.

static void	delivered(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("Message delivered.\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int		byte_i;
	pid_t	pid;

	if (argc != 3)
		exit_error("Client: Wrong amount of arguments");
	else if (kill(ft_atoi(argv[1]), 0) < 0)
		exit_error("Client: given PID is not valid");
	pid = ft_atoi(argv[1]);
	byte_i = 0;
	signal(SIGUSR1, delivered);
	while (argv[2][byte_i])
	{
		// signal confirmation and how to send char
		if (!send_character(argv[2][byte_i]))
			return (1);
		if (!sig_confirmation())
			return (1);
	}
	send_string(argv[2], pid);
	return (0);
}
