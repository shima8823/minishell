/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:29:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/21 13:25:44 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static bool	is_next_pipe(void);

void	run_pipe_in_child(void)
{
	bool	is_next;

	is_next = is_next_pipe();
	close(g_shell.pipe_fd[PIPE_READ]);
	dup2(g_shell.old_read_pipe_fd, STDIN_FILENO);
	if (g_shell.old_read_pipe_fd != 0)
		close(g_shell.old_read_pipe_fd);
	if (is_next)
		dup2(g_shell.pipe_fd[PIPE_WRITE], STDOUT_FILENO);
	close(g_shell.pipe_fd[PIPE_WRITE]);
}

static bool	is_next_pipe(void)
{
	if (g_shell.pipe_len > 1)
		return (true);
	else
		return (false);
}
