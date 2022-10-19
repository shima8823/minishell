/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:29:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 17:18:52 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static bool	is_next_pipe(void);

void	run_pipe_in_child(void)
{
	bool	is_next;

	is_next = is_next_pipe();
	close(g_shell.pipe_fd[PIPE_READ]);
	dup2(g_shell.read_fd, STDIN_FILENO);
	close(g_shell.read_fd);
	if (is_next)
	{
		dup2(g_shell.pipe_fd[PIPE_WRITE], STDOUT_FILENO);
		close(g_shell.pipe_fd[PIPE_WRITE]);
	}
}

static bool	is_next_pipe(void)
{
	if (g_shell.pipe_len > 1)
		return (true);
	else
		return (false);
}
