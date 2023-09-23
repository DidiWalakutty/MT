/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/17 17:37:11 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/23 19:11:26 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_done(char **message, int *done, int user)
{
	if (*done == 1)
	{
		if (user == SIGUSR1)
			*message = print_message(*message);
		free(*message);
		*message = NULL;
		*done = 0;
	}
}

char	*first_letter(char c)
{
	char	*first;

	first = (char *)malloc(sizeof(char) * 256);
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
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
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

void	sig_handler(int user, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;
	static char	*message;
	static int	done;

	(void)context;
	c |= (user == SIGUSR1) << bit;
	usleep(200);
	kill(info->si_pid, SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (c)
			message = add_to_string(message, c);
		else
			done = 1;
		reset_stats(&bit, &c);
	}
	else if (done == 1)
	{
		handle_done(&message, &done, user);
		reset_stats(&bit, &c);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	server_act;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
		ft_printf("Server PID: %d\n", pid);
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
