/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:14:43 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/12 21:05:07 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_shell *shell, char **args)
{
	int	i;
	int	arg;

	i = 0;
	arg = 1;
	if (args[0] == NULL)
		return (0);
	if (ft_strcmp(args[0], "-n") == 0)
		i++;
	while (args[i])
	{
		if (arg > 1)
			ft_printf(" ");
		ft_printf("%s", args[i]);
		i++;
		arg++;
	}
	if (!(ft_strcmp(args[0], "-n") == 0))
		printf("\n");
	shell->exit_status = 0;
	return (0);
}
