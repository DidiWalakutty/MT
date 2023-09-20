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

static void	received_signal(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Received signal\n");
		exit(0);
	}
}

// SIGUSR1 = 1
// SIGUSR2 = 0
// C &(1 << shift): shift left operator: moves the bits to the left, and discards the far left bit. 
static void	send_character(char c, int pid)
{
	int	check;
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		// need to rethink how to use operators here!!!
		// what do I want to compare?
		if (c & (1 << shift))
			check = kill(pid, SIGUSR1);
		else
			check = kill(pid, SIGUSR2);
		if (check != 0)
			exit_error("Failed to send signal");
		usleep(100);
		shift++;
		// signal(SIGUSR1, received_signal); to show it has received a signal?
	}

}

// Client sends the character to the server.
// Kill notifies server that a signal was send.

// Not only does the the PID have to be digits, it also has to be a running process.
// The 'else if' checks if there's a running process with the given number from argv[1].
// 1st 0: The 0 behind it states you don't want to send a message or signal a process, just check if argv[1] exists.
// 2nd 0: If the answer is < 0, it means there was a problem, like no digits or no existing process.
// If it's 0 or > 0 a process with the specified PID exists.
int	main(int argc, char **argv)
{
	int		byte_i;
	pid_t	pid;

	if (argc != 3)
		exit_error("Client: Wrong amount of arguments");
	else if (kill(ft_atoi(argv[1]), 0) < 0)
		exit_error("Client: given PID is not valid");
	pid = ft_atoi(argv[1]);
	// signal(SIGUSR1, received_signal);
	byte_i = 0;
	while (argv[2][byte_i])
		send_character(argv[2][byte_i++], pid);
	while (1)
		pause();
	return (0);
}