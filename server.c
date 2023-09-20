/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/17 17:37:11 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/17 22:12:35 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Server waits to read each character.
// Kill send a signal.

// Server prints out the PID-number and keeps listening for incoming
// message transmissions.
// 1. Check lenght of message
// 2. Chars
// 3. end with \0
// Only print when full string is received.
// For each signal received from client, server sends a corresponding signal back.


// sigemptyset initalizes an empty signal set (set of singals) and often used with sigaction struct.
// sa_mask: a list of isgnals that the program temporarily puts on hold while dealing with a specific signal.
// sa_flags: 
// 		- SA_SIGINFO: program wants to get extra info when a signal happens "who and why was it sent"
//		- SA_RESTART: decides whether the program should continue where it left off after handling a signal, or start over.
//					  like choosing between pausing a movie or let it keep playing while you chat and resume where you left of.

// if bit = 1:
// << bit 	changes the most right bit one to the left
// 00000000 becomes 00000010
// >> bit 	changes the most left bit one to the right
// 00000000 becomes 01000000
//
// |= OR operator: compares two bits.
// | 1 <<: modifies to the bith-position of a to '1'. 
// It uses | OR and bitshift LEFT to set a bit
// at the bith position of char c.
// c = 00000000. If bit is 1, c becomes: 00000010. 
// 
// According to the bit's position and which SIGUSR it is, it'll set
// that bit to either 1 or bit++, because that's already a 0.
void	binary_to_char(int user, char *c)
{
	if (user == SIGUSR1)
	{
		c |= 1 << bit;
		bit++;
	}
	else if (user == SIGUSR2)
		bit++;
}

// Ignore, catch or default.
// Siginfo_t structure contains the PID.
// this info is automatically stored when a signal is received.
// if bit == 8, it has received all 8 bits and can handle the message.
void	sig_handler(int user, siginfo_t *info, void *context)
{
	static int	pid;
	static int	bit = 0;
	static char	c = 0;
	static char *message = 0;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	binary_to_char(user, &c);
	if (bit == 8)
	{
		if (c)
			message = add_to_string(message, c);
		else
			message = print_string(message);
		bit = 0;
		c = 0;
	}
	// usleep();?
	// kill(info->si_pid, SIGUSR2)
}

// sa_mask: any signals that should be blocked while the
// sig_handler is being executed.
// sa_flags: do we get extended information (siginfo) and
// if signals should be restarted when system call was interrupted.	
int	main(void)
{
	struct sigaction	server_act;
	pid_t	pid;

	pid = getpid();
	printf("Server PID: %d\n", pid);
	sigemptyset(&server_act.sa_mask);
	server_act.sa_flags = SA_SIGINFO | SA_RESTART;
	server_act.sa_sigaction = sig_handler;
	set_signals(&server_act);
	while (1)
		pause();
	return (0);
}