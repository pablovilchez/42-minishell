/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:26:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:26:25 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(t_list *new_arg)
{
	if (new_arg->key)
		free(new_arg->key);
	if (new_arg->value)
		free(new_arg->value);
	if (new_arg)
		free(new_arg);
}

void	add_signs(char *res, int i)
{
	res[i] = '=';
	res[i + 1] = '"';
}

char	*write_line(char *str1, char *str2, int len, int init)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = ft_calloc(len, sizeof(char));
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	if (init)
		add_signs(res, i);
	i += 2;
	j = 0;
	while (str2[j])
	{
		res[i] = str2[j];
		j++;
		i++;
	}
	if (init)
		res[i] = '"';
	return (res);
}

char	**fill_str_array(t_list *env_lst, int *lst_size)
{
	char	**str_array;
	int		i;
	int		len;
	int		init;

	i = 0;
	*lst_size = ft_lstsize(env_lst);
	str_array = ft_calloc(*lst_size + 1, sizeof(char *));
	while (i < *lst_size)
	{
		len = (ft_strlen(env_lst->key) + ft_strlen(env_lst->value) + 4);
		init = env_lst->init;
		str_array[i] = write_line(env_lst->key, env_lst->value, len, init);
		env_lst = env_lst->next;
		i++;
	}
	return (str_array);
}

void	export_empty(t_shell *shell)
{
	char	**str_array;
	int		i;
	int		lst_size;

	lst_size = 0;
	str_array = fill_str_array(shell->env_lst, &lst_size);
	sort_array(str_array, lst_size);
	i = 0;
	while (str_array[i])
	{
		ft_printf("declare -x %s\n", str_array[i]);
		free(str_array[i]);
		i++;
	}
	free (str_array);
}
