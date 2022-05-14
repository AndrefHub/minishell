/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:07:26 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/14 20:07:29 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
