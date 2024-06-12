/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:24:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:24:17 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

char	**add_token(char **tokens, char *buff)
{
	char	**aux;
	int		i;

	i = 0;
	while (tokens[i])
		i++;
	aux = (char **)ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (tokens[i])
	{
		aux[i] = tokens[i];
		i++;
	}
	aux[i] = buff;
	free(tokens);
	return (aux);
}

int	chk_end_token(char *input, int *i, int *start)
{
	static int	type;
	static int	used;

	if (*start == 0)
	{
		*start = 1;
		used = 0;
		type = assign_type(input[*i]);
		while (input[*i] && type == 4)
		{
			*i = *i + 1;
			type = assign_type(input[*i]);
		}
	}
	if (!end_token(input[*i], type, &used))
		return (0);
	return (1);
}

char	*read_token(char *input, int *i)
{
	char	*c;
	char	*aux;
	char	*buff;
	int		start;

	c = ft_calloc(sizeof(char), 2);
	buff = ft_calloc(sizeof(char), 1);
	start = 0;
	while (input[*i] && !chk_end_token(input, i, &start))
	{
		c[0] = input[*i];
		aux = buff;
		buff = ft_strjoin(aux, c);
		free(aux);
		*i = *i + 1;
	}
	free(c);
	if (ft_strlen(buff) == 0)
		return (NULL);
	return (buff);
}

void	p_split(char *input, t_shell *shell)
{
	int		i;
	char	**aux;
	char	*buff;
	int		n;

	i = 0;
	n = 0;
	shell->tokens = (char **)ft_calloc(sizeof(char *), 1);
	while (input[i] && ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		buff = read_token(input, &i);
		if (buff)
		{
			aux = add_token(shell->tokens, buff);
			n++;
		}
		shell->tokens = aux;
		while (input[i] && ft_isspace(input[i]))
		{
			shell->space_next[n - 1] = '1';
			i++;
		}
	}
}
