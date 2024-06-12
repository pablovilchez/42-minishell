/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_nodes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:35 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/23 18:35:41 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tcmdsize(t_cmd *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

void	ft_add_front_node(t_cmd **lst, t_cmd *new_node)
{
	if (lst && new_node)
	{
		new_node->next = *lst;
		*lst = new_node;
	}
}

t_cmd	*ft_add_back_node(t_cmd **lst, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (*lst == NULL)
		*lst = new_node;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}
	return (new_node);
}

void	lst_clear_nodes(t_cmd **lst)
{
	t_cmd	*node;
	t_cmd	*aux;

	node = *lst;
	while (node != NULL)
	{
		if (node->cmd[0] == '\0')
			free(node->cmd);
		aux = node;
		node = node->next;
		free(aux->cmd_path);
		free(aux->args);
		free(aux);
	}
	free(lst);
}

t_cmd	*lst_new_node(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	node->cmd = ft_calloc(1, sizeof(char));
	node->cmd_path = ft_calloc(1, sizeof(char));
	node->args = ft_calloc(10, sizeof(char *));
	node->infile = 0;
	node->outfile = 1;
	node->next = NULL;
	return (node);
}
