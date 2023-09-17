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

#include "minishell.h"

void	sig_handler(int user, siginfo_t *info, void *context)
{
	(void)user;
	(void)info;
	(void)context;
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
	struct sigaction	server_act;
	int					byte_i;
	int					pid;

	if (argc != 3)
		exit_error("Client: Wrong amount of arguments");
	else if (kill(ft_atoi(argv[1]), 0) < 0)
		exit_error("Client: given PID is not valid");
	pid = ft_atoi(argv[1]);
	byte_i = 0;
	sigemptyset(&server_act.sa_mask);
	server_act.sa_flags = SA_SIGINFO | SA_RESTART;
	server_act.sa_sigaction = sig_handler;
	set_signals(&server_act);
	// kill(pid, SIGUSR1);
	return (0);
}