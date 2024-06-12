/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_make_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:41 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/26 12:06:09 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_argument(t_shell *shell, char *token, t_cmd *node)
{
	int	i;

	i = 0;
	if (!node->cmd[0])
	{
		update_env(shell);
		if (is_in_path(shell, token) || is_built_in(token))
		{
			node->cmd = str_change_value(node->cmd, token);
			if (!is_built_in(token))
				node->cmd_path = find_path(token, shell->env, node->cmd_path);
		}
		else
		{
			while (node->args[i])
				i++;
			node->args[i] = str_change_value(node->args[i], token);
		}
	}
	else
	{
		while (node->args[i])
			i++;
		node->args[i] = str_change_value(node->args[i], token);
	}
}

int	is_argument(char *token)
{
	int	type;

	type = assign_type(token[0]);
	if (type >= 4)
		return (1);
	else
		return (0);
}

void	clean_nodes_data(t_cmd **exec_nodes, char *input, t_shell *shell)
{
	lst_clear_nodes(exec_nodes);
	free(input);
	free_tokens(shell);
}

void	make_nodes(t_shell *shell, char *input)
{
	int		i;
	t_cmd	**exec_nodes;
	t_cmd	*new_node;

	i = 0;
	shell->fd_in = 0;
	new_node = NULL;
	exec_nodes = ft_calloc(1, sizeof(t_cmd *));
	while (shell->tokens[i])
	{
		new_node = ft_add_back_node(exec_nodes, lst_new_node());
		check_use_fd_in(new_node, shell);
		while (shell->tokens[i])
		{
			put_token(shell, &i, new_node);
			if (type_three(shell, &i))
				break ;
			i++;
		}
	}
	if (!ft_strcmp(shell->tokens[0], "exit" ))
		exit_minishell(shell, shell->tokens);
	if (*exec_nodes)
		execute_nodes(exec_nodes, shell);
	clean_nodes_data(exec_nodes, input, shell);
}
