/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:55:15 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/24 14:32:17 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_env_lst(t_shell *shell, char **envp)
{
	t_list	*env;
	char	*key;
	char	*value;
	int		i;
	char	*limiter;

	i = 0;
	while (envp[i] != NULL)
	{
		limiter = ft_strchr(envp[i], '=');
		if (limiter)
		{
			key = ft_strndup((const char *)envp[i], limiter - envp[i]);
			value = ft_strdup(limiter + 1);
			env = ft_lstnew(key, value);
			env->init = 1;
			ft_lstadd_back(&(shell->env_lst), env);
			free(key);
			free(value);
		}
		i++;
	}
}

t_list	*node_search(t_list *env, char *str)
{
	t_list	*env_key_search;

	env_key_search = env;
	while (env_key_search)
	{
		if (ft_strcmp(env_key_search->key, str) == 0)
			return (env_key_search);
		env_key_search = env_key_search->next;
	}
	return (NULL);
}

int	key_search(t_list *env, char *str)
{
	t_list	*env_key_search;

	env_key_search = env;
	while (env_key_search)
	{
		if (ft_strcmp(env_key_search->key, str) == 0)
			return (0);
		env_key_search = env_key_search->next;
	}
	return (1);
}

void	print_env_variables(t_shell *shell, t_list *env)
{
	t_list	*env_print;

	env_print = env;
	if (env_print == NULL || key_search(env, "PATH") == 1)
	{
		ft_printf("minishell: env: No such file or directory\n");
		shell->exit_status = 127;
	}
	else
	{
		while (env_print != NULL && env_print->init > 0)
		{
			ft_printf("%s=", (char *)env_print->key);
			ft_printf("%s\n", (char *)env_print->value);
			env_print = env_print->next;
		}
		shell->exit_status = 0;
	}
}

void	free_params(t_shell *shell)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (shell->env[i] != NULL)
		free(shell->env[i++]);
	free(shell->env);
	while (shell->env_lst)
	{
		tmp = shell->env_lst;
		shell->env_lst = shell->env_lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(shell);
}
