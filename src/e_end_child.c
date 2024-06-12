/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_end_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:12:53 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/24 13:53:51 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_child(void)
{
	char	**args;
	char	*cmd;

	args = malloc(sizeof (char *) * 3);
	args[0] = ft_strdup("/bin/sleep");
	args[1] = ft_strdup("0");
	args[2] = NULL;
	cmd = ft_strdup("/bin/sleep");
	execve(cmd, args, NULL);
}
