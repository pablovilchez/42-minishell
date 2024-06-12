/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:26:31 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:36:52 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_key_error(t_shell *shell, char *cmd, t_list *arg)
{
	char	*key;
	char	*value;

	key = (char *)(arg->key);
	value = (char *)(arg->value);
	ft_printf("minishell: %s: `%s=%s': invalid identifier\n", cmd, key, value);
	shell->exit_status = 1;
}

int	check_key(t_list *arg, int print, t_shell *shell, char *cmd)
{
	int		i;
	char	*key;

	i = 0;
	key = (char *)(arg->key);
	if (key[0] && (key[0] == '_' || ft_isalpha(key[0])))
	{
		while (key[++i])
		{
			if (ft_isalnum(key[i]) || key[i] == '_')
				i++;
			else
			{
				if (print == 1)
					launch_key_error(shell, cmd, arg);
				return (0);
			}
		}
		return (1);
	}
	if (print == 1)
		launch_key_error(shell, cmd, arg);
	else
		shell->exit_status = 1;
	return (0);
}

void	sort_array(char **str_array, int lst_size)
{
	int		i;
	char	*aux;

	i = 0;
	aux = NULL;
	while (i < lst_size && str_array[i + 1])
	{
		if (ft_strcmp(str_array[i], str_array[i + 1]) > 0)
		{
			aux = str_array[i];
			str_array[i] = str_array[i + 1];
			str_array[i + 1] = aux;
			i = 0;
		}
		else
			i++;
	}
}
