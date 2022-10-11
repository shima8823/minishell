/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:29:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/09 12:47:14 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;
#define PIPE_READ 0
#define PIPE_WRITE 1

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
		close(fd[PIPE_READ]);
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
		printf("test1\n");
		if (p_info->next != NULL)
		{
			dup2(fd[PIPE_WRITE], STDOUT_FILENO);
			close(fd[PIPE_WRITE]);
		}
		printf("test2\n");
		if (execve(p_info->cmd,p_info->arg,environ) == -1)
			return (-1);
	}
	printf("pid == %d\n", pid);
	// waitpid(pid, NULL, 0);
	printf("pipe finish\n");
	return (fd[0]);
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
	// p_info_2.next = &p_info_1;
	p_info_2.next = NULL;
	fdd = ft_pipe(&p_info_1, 0);
	printf("first pipe finish\n");
	fdd = ft_pipe(&p_info_2, fdd);
	argv2[1] = "o";
	// fdd = ft_pipe(&p_info_2, fdd);
	return 0;
}

