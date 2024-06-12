/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:55:17 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/10 10:47:29 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_shell *shell)
{
	if (getcwd(shell->path, 128) != NULL)
	{
		ft_printf("%s\n", shell->path);
		shell->exit_status = 0;
	}
	else
	{
		perror(shell->path);
		shell->exit_status = errno;
	}
}
