/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:29:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/12 12:13:06 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	link_pipe(int fd[2], int read_fd, t_pipe *p_info);
extern char **environ;

int ft_pipe(t_pipe *p_info, int read_fd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(fd[PIPE_READ]);
		close(fd[PIPE_WRITE]);
		return (-1);
	}
	if (pid == 0)
	{
		link_pipe(fd, read_fd, p_info);
		execve(p_info->cmd,p_info->arg, environ);
	}
	close(fd[PIPE_WRITE]);
	return (fd[PIPE_READ]);
}

static void	link_pipe(int fd[2], int read_fd, t_pipe *p_info)
{
	close(fd[PIPE_READ]);
	dup2(read_fd, STDIN_FILENO);
	close(read_fd);
	if (p_info->next != NULL)
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	close(fd[PIPE_WRITE]);
}

int main(void)
{
	t_pipe p_info_1;
	t_pipe p_info_2;
	char *argv1[2];
	char *argv2[3];
	int fdd;

	p_info_1.cmd = "/bin/ls";
	argv1[0] = "ls";
	argv1[1] = NULL;
	p_info_1.arg = argv1;
	p_info_1.next = &p_info_2;
	p_info_2.cmd = "/usr/bin/grep";
	argv2[0] = "grep";
	argv2[1] = "a";
	argv2[2] = NULL;
	p_info_2.arg = argv2;
	p_info_2.next = &p_info_1;
	// p_info_2.next = NULL;
	fdd = ft_pipe(&p_info_1, 0);
	fdd = ft_pipe(&p_info_2, fdd);
	argv2[1] = "o";
	fdd = ft_pipe(&p_info_2, fdd);
	argv2[1] = "f";
	p_info_2.next = NULL;
	fdd = ft_pipe(&p_info_2, fdd);
	return 0;
}

