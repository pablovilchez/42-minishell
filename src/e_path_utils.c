/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_path_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:29 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/26 14:31:25 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(char **str_list, char *empty_str)
{
	int		i;

	i = 0;
	while (str_list[i])
	{
		free(str_list[i]);
		i++;
	}
	if (empty_str)
		free(empty_str);
	free(str_list);
}

char	**find_path_helper(char **envp)
{
	int		i;
	char	**path_list;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
	{
		if (envp[i + 1] == NULL)
			return (0);
		i++;
	}
	path_list = ft_split(envp[i] + 5, ':');
	return (path_list);
}

char	*find_path(char *command, char **envp, char *empty_str)
{
	char	**path_list;
	char	*path_root;
	char	*final_path;
	int		i;

	path_list = find_path_helper(envp);
	if (path_list == 0)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		path_root = ft_strjoin(path_list[i], "/");
		final_path = ft_strjoin(path_root, command);
		free(path_root);
		if (access(final_path, X_OK) == 0)
		{
			free_path(path_list, empty_str);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_path(path_list, empty_str);
	return (0);
}

int	is_in_path(t_shell *shell, char *str)
{
	char	*aux;
	char	*empty_str;

	empty_str = NULL;
	aux = find_path(str, shell->env, empty_str);
	if (aux)
	{
		free(aux);
		return (1);
	}
	else
		return (0);
}
