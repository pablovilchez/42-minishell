/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:23 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/27 12:48:46 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_interactive(void)
{
	rl_on_new_line();
	if (g_shell_state == ENDED_HERE_DOC)
		write(1, "> ", 2);
	rl_redisplay();
	write(1, "\033[K\n", 5);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_shell_state = CTRL_C;
}

void	is_sigint(int signal)
{
	(void)signal;
	if (g_shell_state == INIT || g_shell_state == CTRL_C
		|| g_shell_state == ENDED_HERE_DOC)
		signal_interactive();
	else
	{
		if (g_shell_state == IN_HERE_DOC)
			ioctl(0, TIOCSTI, "\n");
		else
			write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_shell_state = CTRL_C_IN_COMMAND;
	}
}

void	setup_signal_handling(void)
{
	signal(SIGINT, is_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
