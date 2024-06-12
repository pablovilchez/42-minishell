/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dollar_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:24:26 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:24:27 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varible_search(t_list *env_lst, char **var, int flag)
{
	if (env_lst == NULL)
		return (1);
	while (env_lst->next != NULL && flag == 0)
	{
		if (ft_strcmp(*var, env_lst->key) == 0)
		{
			free(*var);
			*var = strdup(env_lst->value);
			return (0);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

char	*after_dolor_sign(t_shell *shell, char *str, int i)
{
	int		start;
	char	*var;
	int		flag;

	start = i;
	flag = 0;
	if (str[i] == ' ' || str[i] == '\0')
	{
		var = ft_strdup("$");
		return (var);
	}
	if (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		start++;
		flag = 1;
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var = ft_substr(str, start, i - start);
	varible_search(shell->env_lst, &var, flag);
	return (var);
}

char	*str_after_var(char *str, int pos)
{
	char	*str_end;

	while (str[pos] && (ft_isalnum(str[pos]) != 0 || str[pos] == '_'))
		pos++;
	str_end = ft_substr(str, pos, ft_strlen(str) - pos + 1);
	return (str_end);
}

char	*ft_cat(char *str, char *var, char *str_end, int *pos)
{
	char	*before_str;
	char	*new_str;
	char	*new_token;
	int		aux;

	aux = *pos;
	before_str = ft_strndup((const char *)str, (size_t)aux);
	new_str = ft_strjoin(before_str, var);
	*pos = ft_strlen(new_str);
	free(before_str);
	free(var);
	new_token = ft_strjoin(new_str, str_end);
	free(new_str);
	free(str_end);
	free(str);
	return (new_token);
}

void	ft_token_check(t_shell *shell, char *str, int i)
{
	int		j;
	char	*str_end;
	char	*var;

	(void)str;
	str = shell->tokens[i];
	j = 0;
	while (shell->tokens[i][j])
	{
		if (shell->tokens[i][j] == '$')
		{
			if (shell->tokens[i][j + 1] == '?')
				break ;
			str_end = str_after_var(shell->tokens[i], j + 1);
			var = after_dolor_sign(shell, shell->tokens[i], j + 1);
			if (var)
			{
				shell->tokens[i] = ft_cat(shell->tokens[i], var, str_end, &j);
			}
			else
				break ;
		}
		j++;
	}
}
