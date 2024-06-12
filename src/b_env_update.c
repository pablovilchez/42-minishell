/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:58:35 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/26 11:00:56 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_var(t_shell *shell)
{
	int		i;
	t_list	*env_lst_cpy;

	i = 0;
	env_lst_cpy = shell->env_lst;
	while (env_lst_cpy)
	{
		i++;
		env_lst_cpy = env_lst_cpy->next;
	}
	return (i);
}

char	*concat_env(t_list *env_lst_cpy, char **env, int pos)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = ft_strdup(env_lst_cpy->key);
	tmp = ft_strjoin(key, "=");
	free(key);
	value = ft_strdup(env_lst_cpy->value);
	env[pos] = ft_strjoin(tmp, value);
	free (tmp);
	free(value);
	return (env[pos]);
}

char	**ft_stddup_env(t_shell *shell)
{
	int		i;
	char	**env;
	t_list	*env_lst_cpy;

	i = 0;
	env_lst_cpy = shell->env_lst;
	env = malloc(sizeof(char *) * (count_env_var(shell) + 1));
	if (!env)
		return (NULL);
	while (env_lst_cpy)
	{
		env[i] = concat_env(env_lst_cpy, env, i);
		i++;
		env_lst_cpy = env_lst_cpy->next;
	}
	env[i] = NULL;
	return (env);
}

void	update_env(t_shell *shell)
{
	if (count_env_var(shell) > 0)
	{
		free_args(shell->env);
		shell->env = ft_stddup_env(shell);
	}
	else
		printf("Error\n");
}
