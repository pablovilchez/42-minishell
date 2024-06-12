/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_make_nodes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:46 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/24 16:19:22 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_invalid(char *cmd_old, char *cmd_new)
{
	if (ft_strcmp(cmd_old, cmd_new))
	{
		if (!ft_strcmp("export", cmd_new) || !ft_strcmp("unset", cmd_new)
			|| !ft_strcmp("exit", cmd_new))
			return (1);
		else if (!ft_strcmp("cd", cmd_old))
			return (2);
	}
	return (0);
}

int	is_built_in(char *token)
{
	int		i;
	char	*token_cpy;

	token_cpy = convert_lowercase(token);
	if (ft_strcmp(token_cpy, "env") == 0)
		i = 1;
	else if (ft_strcmp(token_cpy, "export") == 0)
		i = 1;
	else if (ft_strcmp(token_cpy, "unset") == 0)
		i = 1;
	else if (ft_strcmp(token_cpy, "cd") == 0)
		i = 1;
	else if (ft_strcmp(token_cpy, "echo") == 0)
		i = 1;
	else if (ft_strcmp(token_cpy, "pwd") == 0)
		i = 1;
	else if (ft_strcmp(token_cpy, "exit") == 0)
		i = 1;
	else
		i = 0;
	free(token_cpy);
	return (i);
}

void	check_redir(t_cmd *node, int *i, t_shell *shell, int plus)
{
	int		fd[2];

	pipe(fd);
	if (ft_strcmp(shell->tokens[*i], "|") == 0)
		token_pipe(node, fd, shell);
	else if (ft_strcmp(shell->tokens[*i], "<") == 0)
		token_input(shell->tokens, i, node);
	else if (ft_strcmp(shell->tokens[*i], ">") == 0)
		token_output(shell->tokens, i, node);
	else if (ft_strcmp(shell->tokens[*i], ">>") == 0)
		token_output_cat(shell->tokens, i, node);
	else if (ft_strcmp(shell->tokens[*i], "<<") == 0)
		token_heredoc(shell->tokens, i, node);
	*i = *i + plus;
}

char	*str_change_value(char *old_str, char *new_str)
{
	free(old_str);
	old_str = new_str;
	return (new_str);
}

void	check_use_fd_in(t_cmd *new_node, t_shell *shell)
{
	if (shell->fd_in != 0)
	{
		new_node->infile = shell->fd_in;
		shell->fd_in = 0;
	}
}
