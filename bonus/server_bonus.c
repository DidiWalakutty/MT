/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/17 17:37:11 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/22 19:40:38 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*print_string(char *message)
{
	ft_putstr_fd(message, 1);
	free(message);
	return (NULL);
}

char	*first_letter(char c)
{
	char	*first;

	first = (char *)malloc(sizeof(char) * 2);
	if (!first)
		return (NULL);
	first[0] = c;
	first[1] = '\0';
	return (first);
}

char	*add_to_string(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (first_letter(c));
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2)); // 256
	if (!add)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		add[i] = str[i];
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

// Ignore, catch or default.
// Siginfo_t structure contains the PID.
// this info is automatically stored when a signal is received.
// if bit == 8, it has received all 8 bits and can handle the message.
void	sig_handler(int user, siginfo_t *info, void *context)
{
	pid_t	pid;
	static int	bit;
	static char	c;
	static char	*message;
	static int	done;

	(void)context;
	pid = info->si_pid;
	c |= (user == SIGUSR1) << bit;
	usleep(100);
	kill(pid, user);
	bit++;
	if (bit == 8)
	{
		if (c)
			message = add_to_string(message, c);
		else
			done = 1;
		bit = 0;
		c = 0;
	}
	else if (done == 1)
	{
		// andere functie
		if (user == SIGUSR1)
			message = print_string(message);
		free(message);
		message = NULL;
		bit = 0;
		c = 0;
		done = 0;
	}
}

// sa_mask: any signals that should be blocked while the
// sig_handler is being executed.
// sa_flags: do we get extended information (siginfo) and
// if signals should be restarted when system call was interrupted.
// pause: sleeps untill it receives a signal.
int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	server_act;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
		printf("Server PID: %d\n", pid);
		sigemptyset(&server_act.sa_mask);
		server_act.sa_sigaction = sig_handler;
		server_act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &server_act, NULL) < 0)
			exit_error("Couldn't set up SIGUSR1");
		if (sigaction(SIGUSR2, &server_act, NULL) < 0)
			exit_error("Couldn't set up SIGUSR2");
		while (1)
			pause();
	}
	return (0);
}
