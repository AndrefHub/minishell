/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:11:54 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/14 20:11:55 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_sig_handler(void (*handler) (int, siginfo_t *, void *))
{
	struct sigaction	sigact;

	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}

void	parent_sig_handler(int sigsum, siginfo_t *sig, void *context)
{
	if (sigsum == SIGINT)
		clear_term_signal();
	else if (sigsum == SIGQUIT)
		print_nothing(1);
	(void ) sig;
	(void ) context;
}

void	clear_child_input(void)
{
	int		exit_status;
	pid_t	pid;

	pid = waitpid(-1, &exit_status, 0);
	while (pid != -1)
		pid = waitpid(-1, &exit_status, 0);
	write(2, "\n", 1);
}

void	child_sig_handler(int sigsum, siginfo_t *sig, void *context)
{
	if (sigsum == SIGINT)
		clear_child_input();
	if (sigsum == SIGQUIT)
		write(2, "Quit: 3\n", 8);
	(void ) sig;
	(void ) context;
}
