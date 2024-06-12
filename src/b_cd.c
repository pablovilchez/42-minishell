/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:26:45 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/26 14:29:33 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	abs_path(t_shell *shell, char *path)
{
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		ft_printf("minishell: cd: %s not set\n", shell->env_lst->key);
		shell->exit_status = 1;
	}
	else
		ft_export_pwds(shell, old_dir, path, path);
}

void	home_cd(t_shell *shell, char *path, char *args)
{
	char	*new_dir;
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		ft_printf("minishell: cd: %s not set\n", shell->env_lst->key);
		shell->exit_status = 1;
	}
	else
	{
		if (ft_strcmp(path, "/") == 0)
			new_dir = ft_strdup("/");
		else
			new_dir = get_value(shell, path);
		if (new_dir != NULL)
		{
			ft_export_pwds(shell, old_dir, new_dir, args);
			if (ft_strcmp(path, "OLDPWD") == 0)
				ft_printf("%s\n", get_value(shell, "PWD"));
			else if (ft_strcmp(path, "/") == 0)
				free (new_dir);
		}
	}
}

void	parent_dir(t_shell *shell, char *args)
{
	char	*new_dir;
	char	*old_dir;
	char	*last_slash;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		ft_printf("minishell: cd: %s not set\n", shell->env_lst->key);
		shell->exit_status = 1;
	}
	else
	{
		new_dir = ft_strdup(old_dir);
		last_slash = ft_strrchr(new_dir, '/');
		if (last_slash != NULL && new_dir != last_slash)
			*last_slash = '\0';
		else if (last_slash != NULL && new_dir == last_slash)
		{
			free(new_dir);
			new_dir = ft_strdup("/");
		}
		ft_export_pwds(shell, old_dir, new_dir, args);
		free (new_dir);
	}
}

void	cd(t_shell *shell, char *args)
{
	int		i;

	i = 0;
	if (args == NULL)
		home_cd(shell, "HOME", args);
	else if (ft_strcmp(args, "/") == 0)
		home_cd(shell, "/", args);
	else
	{
		if (ft_strcmp(args, ".") == 0 && args[i + 1])
			i = 1;
		if (ft_strcmp(&args[i], "-") == 0)
			home_cd(shell, "OLDPWD", &args[i]);
		else if (ft_strcmp(&args[i], "~") == 0)
			home_cd(shell, "HOME", &args[i]);
		else if (ft_strcmp(&args[i], "..") == 0)
			parent_dir(shell, &args[i]);
		else
			abs_path(shell, &args[i]);
	}
}
