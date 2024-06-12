/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:23:40 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:33:09 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_pipe(t_cmd *node, int *fd, t_shell *shell)
{
	if (node->outfile == 1)
		node->outfile = fd[1];
	shell->fd_in = fd[0];
}

void	token_input(char **tokens, int *i, t_cmd *node)
{
	int	fd;

	if (tokens[*i + 1])
	{
		fd = open(tokens[*i + 1], O_RDONLY, 0777);
		node->infile = fd;
		*i = *i + 1;
	}
}

void	token_output(char **tokens, int *i, t_cmd *node)
{
	int	fd;

	if (tokens[*i + 1])
	{
		fd = open(tokens[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		node->outfile = fd;
		*i = *i + 1;
	}
}

void	token_output_cat(char **tokens, int *i, t_cmd *node)
{
	int	fd;

	if (tokens[*i + 1])
	{
		fd = open(tokens[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		node->outfile = fd;
		*i = *i + 1;
	}
}
