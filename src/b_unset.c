/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:26:08 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/19 14:38:27 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_shell *shell, t_list *node)
{
	if (!ft_strcmp(node->key, "PATH"))
		shell->env_path = 0;
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	delete_value(t_shell *shell, int node_pos)
{
	t_list	*node;
	t_list	*aux;
	int		i;

	node = shell->env_lst;
	if (node_pos == 0)
	{
		aux = node;
		shell->env_lst = shell->env_lst->next;
		free_node(shell, aux);
	}
	else
	{
		i = 0;
		while (i < node_pos)
		{
			aux = node;
			node = node->next;
			i++;
		}
		aux->next = node->next;
		free_node(shell, node);
	}
}

void	unset(t_shell *shell, char **args)
{
	t_list	*lst;
	int		i;
	int		found;
	t_list	*new_arg;
	int		node_pos;

	i = 0;
	while (args[i])
	{
		found = 0;
		node_pos = 0;
		new_arg = ft_calloc(1, sizeof(t_list));
		lst = shell->env_lst;
		extract_values(args[i], new_arg);
		while (lst && found == 0 && check_key(new_arg, 1, shell, "unset"))
		{
			if (key_found(new_arg->key, (char *)lst->key, &found))
				delete_value(shell, node_pos);
			lst = lst->next;
			node_pos++;
		}
		free_arg(new_arg);
		i++;
	}
}
