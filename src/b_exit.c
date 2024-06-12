/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:39:58 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/23 20:39:34 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, long i, char *args)
{
	shell->exit_status = i % 256;
	if (!ft_strcmp(args, "~"))
	{
		free(args);
		args = getenv("HOME");
	}
	printf("exit\nminishell: exit: %s: ", args);
	if (i == 1)
		printf("too many arguments\n");
	else if (i == 255)
		printf("numeric argument required\n");
	if (i != 1)
	{
		free(shell->space_next);
		free_params(shell);
		exit(shell->exit_status);
	}
	else
		return (shell->exit_status);
}

int	various_args(t_shell *shell, char **args, long i)
{
	int		j;

	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (i > 1)
			{
				ft_exit(shell, 1, args[1]);
				return (shell->exit_status);
			}
			if (!ft_isdigit(args[i][j]) && i == 1)
				ft_exit(shell, 255, args[1]);
			j++;
		}
		i++;
	}
	return (0);
}

void	exit_minishell(t_shell *shell, char **args)
{
	long	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == 124)
			return ;
		i++;
	}
	if (args[1] == NULL)
	{
		shell->exit_status = 0;
		exit(0);
	}
	else if (!various_args(shell, args, 1))
	{
		i = ft_long_atoi(args[1]);
		shell->exit_status = i % 256;
		free(shell->space_next);
		free_params(shell);
		printf("exit\n");
		exit(shell->exit_status);
	}
}
