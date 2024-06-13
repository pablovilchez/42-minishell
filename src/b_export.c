/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:26:18 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:26:20 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_value(t_list *env_list, t_list *new_arg)
{
	char	*aux;
	int		len;

	len = ft_strlen(new_arg->value);
	aux = env_list->value;
	env_list->value = ft_calloc(len + 1, 1);
	if (new_arg->init == 1)
		env_list->init = 1;
	ft_strlcpy(env_list->value, new_arg->value, len + 1);
	free(aux);
}

void	create_key(t_list *env_list, t_list *new_arg)
{
	t_list	*new_key;

	new_key = ft_lstnew(new_arg->key, new_arg->value);
	new_key->init = new_arg->init;
	ft_lstadd_back(&env_list, new_key);
}

int	key_found(char *arg_key, char *env_key, int *found)
{
	int	i;

	i = 0;
	while (arg_key[i] && env_key[i] && arg_key[i] == env_key[i])
		i++;
	if (env_key[i] == '=' || env_key[i] == '\0')
	{
		*found = 1;
		return (1);
	}
	return (0);
}

void	extract_values(char *arg, t_list *new_arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_arg->key = ft_calloc(ft_strlen(arg) + 1, 1);
	new_arg->value = ft_calloc(ft_strlen(arg) + 1, 1);
	while (arg[i] && arg[i] != '=')
	{
		ft_memcpy(&((char*)new_arg->key)[i], &arg[i], 1);
		i++;
	}
	if (arg[i] == '=')
	{
		new_arg->init = 1;
		i++;
	}
	else
		new_arg->init = 0;
	while (arg[i])
	{
		ft_memcpy(&((char*)new_arg->value)[j], &arg[i], 1);
		i++;
		j++;
	}
}

void	export(t_shell *shell, char **args)
{
	t_list	*lst;
	int		i;
	int		found;
	t_list	*new_arg;

	i = 0;
	while (args[i])
	{
		found = 0;
		new_arg = ft_calloc(1, sizeof(t_list));
		lst = shell->env_lst;
		extract_values(args[i], new_arg);
		while (lst && found == 0 && check_key(new_arg, 1, shell, "export"))
		{
			if (key_found(new_arg->key, (char *)lst->key, &found))
				copy_value(lst, new_arg);
			lst = lst->next;
		}
		if (!found && check_key(new_arg, 0, shell, "export"))
			create_key(shell->env_lst, new_arg);
		free_arg(new_arg);
		i++;
	}
	if (i == 0)
		export_empty(shell);
}
