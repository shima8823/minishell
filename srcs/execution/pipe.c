/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:29:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 10:27:34 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static bool	is_next_pipe(void);
void	ft_pipe(int read_fd, int fd[2], bool is_next);

void	run_pipe_in_parent(void)
{
	bool	is_next;

	is_next = is_next_pipe();
	ft_pipe(g_shell.read_fd, g_shell.fd, is_next);
	if (g_shell.read_fd != 0)
		close(g_shell.read_fd);
}

void	run_pipe_in_child(void)
{
	bool	is_next;

	is_next = is_next_pipe();
	ft_pipe(g_shell.read_fd, g_shell.fd, is_next);
	if (g_shell.read_fd != 0)
		close(g_shell.read_fd);
}

static bool	is_next_pipe(void)
{
	if (g_shell.pipe_len > 1)
		return (true);
	else
		return (false);
}

void	ft_pipe(int read_fd, int fd[2], bool is_next)
{
	close(fd[PIPE_READ]);
	dup2(read_fd, STDIN_FILENO);
	close(read_fd);
	if (is_next)
	{
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
		close(fd[PIPE_WRITE]);
	}
	return ;
}

// int main(void)
// {
// 	int	fd[2];
// 	int	fd2[2];
// 	int	fd3[2];

// 	if (pipe(fd) < 0)
// 		return (1);
// 	g_shell.pid = fork();
// 	if (g_shell.pid == 0)
// 	{
// 		ft_pipe(0, fd, true);
// 		if(execlp("ls", "ls", NULL) == -1)
// 			perror("execlp");
// 	}
// 	close(fd[PIPE_WRITE]);
// 	if (pipe(fd2) < 0)
// 		return (2);
// 	g_shell.pid = fork();
// 	if (g_shell.pid == 0)
// 	{
// 		ft_pipe(fd[PIPE_READ], fd2, true);
// 		if(execlp("grep", "grep", "o", NULL) == -1)
// 			perror("execlp");
// 	}
// 	close(fd2[PIPE_WRITE]);
// 	if (pipe(fd3) < 0)
// 		return (2);
// 	g_shell.pid = fork();
// 	if (g_shell.pid == 0)
// 	{
// 		ft_pipe(fd2[PIPE_READ], fd3, false);
// 		if(execlp("grep", "grep", "a", NULL) == -1)
// 			perror("execlp");
// 	}
// 	close(fd3[PIPE_WRITE]);
// 	close(fd[PIPE_READ]);
// 	close(fd2[PIPE_READ]);
// 	close(fd3[PIPE_READ]);
// 	return 0;
// }
