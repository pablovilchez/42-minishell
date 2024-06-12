/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_trim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:23:56 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/26 14:31:08 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	solve_quotes(int *quotes, char *c)
{
	if (*quotes == 0)
	{
		*quotes = 2 - (*c % 2);
		c[0] = '\0';
	}
	else if ((*quotes == 1 && *c == 39) || (*quotes == 2 && *c == 34))
	{
		*quotes = 0;
		c[0] = '\0';
	}
}

char	*add_char(char *new_token, char *c, int *j)
{
	char	*aux;

	aux = new_token;
	new_token = ft_strjoin(aux, c);
	*j = *j + 1;
	free(aux);
	return (new_token);
}

void	change_token_value(char *new_token, t_shell *shell, int *i)
{
	free(shell->tokens[*i]);
	shell->tokens[*i] = new_token;
	*i = *i + 1;
}

int	syntax_check(char **tokens, t_shell *shell)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (tokens[i] && tokens[i + 1])
	{
		found += redir_check(tokens[i], tokens[i + 1]);
		if (found == 2)
		{
			printf("minishell: syntax error: unexpected end of file\n");
			shell->exit_status = 258;
			return (0);
		}
		else if (found == 3)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				tokens[i]);
			shell->exit_status = 258;
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_trim_tokens(t_shell *shell)
{
	int		i;
	int		j;
	int		quotes;
	char	*new_token;
	char	*c;

	i = 0;
	while (shell->tokens[i])
	{
		new_token = ft_calloc(1, sizeof(char));
		quotes = 0;
		j = 0;
		while (shell->tokens[i][j])
		{
			c = ft_calloc(2, sizeof(char));
			c[0] = shell->tokens[i][j];
			if (*c == 39 || *c == 34)
				solve_quotes(&quotes, c);
			if (*c == '$' && quotes != 1)
				c = find_var(shell, c, &shell->tokens[i][j], &j);
			new_token = add_char(new_token, c, &j);
			free(c);
		}
		change_token_value(new_token, shell, &i);
	}
}
