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

#include "minishell.h"

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


void	binary_to_char(int user, char *c)
{
	if (user == SIGUSR1)
		// do this;
	else if (user == SIGUSR2)
		// do this;
}

// Ignore, catch or default.
// Siginfo_t structure contains the PID.
// this info is automatically stored when a signal is received.
void	sig_handler(int user, siginfo_t *info, void *context)
{
	static int	pid;
	static char	c;
	static int	i;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	binary_to_char(user, &c);
	// 
}

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
}