/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:19:23 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:52:23 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	backup_fd(void)
{
	g_shell.backup_fd[0] = dup(STDIN_FILENO);
	g_shell.backup_fd[1] = dup(STDOUT_FILENO);
}

void	restore_fd(void)
{
	wdup2(g_shell.backup_fd[0], STDIN_FILENO);
	wdup2(g_shell.backup_fd[1], STDOUT_FILENO);
	wclose(g_shell.backup_fd[0]);
	wclose(g_shell.backup_fd[1]);
	g_shell.backup_fd[0] = 0;
	g_shell.backup_fd[1] = 0;
}
