/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/27 12:49:21 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_shell_state;

void	final_cleanup(t_shell *shell, char *input)
{
	if (input)
		free (input);
	else if (!input)
		printf("exit\n");
	free(shell->space_next);
	free_params(shell);
}

char	*zero(t_shell *shell)
{
	char	*input;
	int		i;

	i = 0;
	while (i < 50)
	{
		shell->space_next[i] = '0';
		i++;
	}
	if (g_shell_state != ENDED_HERE_DOC)
		g_shell_state = INIT;
	input = readline("minishell> ");
	if (g_shell_state == CTRL_C)
		shell->exit_status = 1;
	g_shell_state = RUNNING;
	return (input);
}

void	ft_init(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->env_lst = NULL;
	shell->tokens = NULL;
	shell->exit_status = 0;
	shell->space_next = NULL;
	shell->lvl = 1;
	shell->fd_in = 0;
	shell->stdincpy = 0;
	shell->stdoutcpy = 0;
	shell->env_path = 1;
	parse_env(shell, envp);
	shell->space_next = ft_calloc(50, sizeof(char));
}

void	run_input(char *input, t_shell *shell)
{
	add_history(input);
	if (!empty_input(input))
	{
		p_split(input, shell);
		ft_trim_tokens(shell);
		if (syntax_check(shell->tokens, shell))
			make_nodes(shell, input);
		else
		{
			free_tokens(shell);
			free (input);
		}
	}
	else
		free (input);
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_shell				*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	ft_init(shell, envp);
	while (1)
	{
		setup_signal_handling();
		input = zero(shell);
		if (!input)
			break ;
		if (ft_strlen(input) > 0)
			run_input(input, shell);
		else
			free(input);
	}
	final_cleanup(shell, input);
	return (0);
}
