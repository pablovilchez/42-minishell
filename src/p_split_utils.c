/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:24:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/26 14:34:55 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_check(char *str, char *str_next)
{
	int	i;

	i = 0;
	if (str[i] && str[i + 1])
	{
		if ((str[i] == '|' || str[i] == '>')
			&& (str[i + 1] == '|' || str[i + 1] == '>'))
			return (2);
	}
	else if (str[i] && str_next[i])
	{
		if ((str[i] == '|' || str[i] == '>')
			&& (str_next[i] == '|' || str_next[i] == '>'))
			return (1);
	}
	return (0);
}

int	assign_type(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '|')
		return (3);
	else if (ft_isspace(c))
		return (4);
	else if (c == '"')
		return (5);
	else if (c == 39)
		return (6);
	else
		return (7);
}

int	end_token(char c, int type, int *used)
{
	int	new_type;

	new_type = assign_type(c);
	if (type == new_type || type >= 5)
	{
		if (type >= 5 && *used % 2 == 0 && new_type < 5)
			return (1);
		if (type == 1 && c == '<')
			*used = *used + 1;
		if (type == 2 && c == '>')
			*used = *used + 1;
		if (type == 3 && c == '|')
			*used = *used + 1;
		if (type == 5 && c == '"')
			*used = *used + 1;
		if (type == 6 && c == 39)
			*used = *used + 1;
		if (type >= 1 && type <= 3 && *used > 2)
			return (1);
		return (0);
	}
	return (1);
}

void	free_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens[i])
	{
		free(shell->tokens[i]);
		i++;
	}
	free(shell->tokens);
}
