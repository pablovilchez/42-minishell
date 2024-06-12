/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_make_nodes_utils_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/23 18:20:15 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_lowercase(char *token)
{
	int		i;
	char	*token_cpy;

	i = 0;
	token_cpy = ft_strdup(token);
	while (token_cpy[i])
	{
		token_cpy[i] = ft_tolower(token_cpy[i]);
		i++;
	}
	token_cpy[i] = '\0';
	return (token_cpy);
}

void	put_token(t_shell *shell, int *i, t_cmd *new_node)
{
	if (is_argument(shell->tokens[*i]))
		add_argument(shell, shell->tokens[*i], new_node);
	else
		check_redir(new_node, i, shell, 0);
}

int	type_three(t_shell *shell, int *i)
{
	if (assign_type(shell->tokens[*i][0]) == 3)
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}
