/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:35:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/13 15:08:31 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_level(char *lvl)
{
	int		level;
	char	*result;
	int		i;

	i = 0;
	while (lvl[i])
	{
		if (ft_isdigit(lvl[i]) == 0)
		{
			lvl = ft_strdup("1");
			return (lvl);
		}
		i++;
	}
	level = ft_atoi(lvl);
	level += 1;
	result = ft_itoa(level);
	return (result);
}

void	update_level(t_shell *shell, int flag)
{
	char	**lvl;
	t_list	*aux;

	if (flag == 1 && key_search(shell->env_lst, "SHLVL") == 1)
	{
		lvl = ft_calloc(2, sizeof(char *));
		lvl[0] = ft_strdup("SHLVL=1");
		export(shell, lvl);
	}
	else if (flag == 1 && key_search(shell->env_lst, "SHLVL") == 0)
	{
		lvl = ft_calloc(3, sizeof(char *));
		aux = node_search(shell->env_lst, "SHLVL");
		lvl[0] = check_level(aux->value);
		lvl[1] = ft_strjoin("SHLVL=", lvl[0]);
		if (lvl[0] != NULL && lvl[1] != NULL)
			export(shell, &lvl[1]);
		free_args(lvl);
	}
	update_env(shell);
}

void	parse_env(t_shell *shell, char **envp)
{
	shell->env = ft_strddup((const char **)envp);
	create_env_lst(shell, envp);
}

char	*ft_strndup(const char *str, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}

char	**ft_strddup(const char **envp)
{
	int		i;
	char	**env;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (0);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
