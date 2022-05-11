#include "../../minishell.h"

void	parent_sig_handler(int sigsum, siginfo_t *sig, void *context)
{
	if (sigsum == SIGINT)
		clear_term_signal();
	else if (sigsum == SIGQUIT)
		print_nothing(1);
	(void ) sig;
	(void ) context;
}

void	child_sig_handler(int sigsum, siginfo_t *sig, void *context)
{
	if (sigsum == SIGINT)
		write(1, "\n", 1);
	if (sigsum == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	(void ) sig;
	(void ) context;
}

void	clear_term_signal(void )
{
	print_nothing(1);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	print_nothing(1);
}

void	print_nothing(int mode)
{
	rl_on_new_line();
	if (mode)
		rl_redisplay();
}

void setup_term(void)
{
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	init_sig_handler(void (*handler) (int, siginfo_t *, void *))
{
	setup_term();
	struct sigaction sigact;
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}