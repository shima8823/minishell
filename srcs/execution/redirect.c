/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:20:46 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/14 11:46:01 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output_redirect(t_command cmd)
{
	int	fd;

	fd = open(cmd.filename, O_CREAT | O_WRONLY | O_TRUNC, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	output_redirect_append(t_command cmd)
{
	int	fd;

	fd = open(cmd.filename, O_WRONLY | O_CREAT | O_APPEND, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	input_redirect(t_command cmd)
{
	int	fd;

	fd = open(cmd.filename, O_RDONLY);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	input_redirect_here(t_command cmd)
{
	char	*line;
	char	*res;
	char	*tmp;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	res = malloc(1);
	if (!res)
	{
		perror("malloc");
		return ;
	}
	while(1)
	{
		line = readline(">");
		if (!line)
			break;
		if (ft_strncmp(cmd.filename, line, ft_strlen(cmd.filename)) == 0)
		{
			free(line);
			break; ;
		}
		tmp = res;
		res = ft_strjoin(res, line);
		if (!res)
		{
			perror("malloc");
			return ;
		}
		if (tmp)
			free(tmp);
		free(line);
	}
	ft_putstr_fd(res, fd[PIPE_WRITE]);
	dup2(fd[PIPE_READ], STDIN_FILENO);
	close(fd[PIPE_READ]);
	close(fd[PIPE_WRITE]);
	free(res);
}

extern char **environ;
int main(void)
{
	t_command cmd;
	int	bu;
	char *args[3];

	args[0] = "grep";
	args[1] = "a";
	args[2] = NULL;
	// cmd.filename = "./func_playground/test.txt";
	cmd.filename = "test";
	// bu = dup(1);
	input_redirect_here(cmd);
	execve("/usr/bin/grep", args, environ);
	return 0;
}
