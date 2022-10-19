/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:20:46 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/14 12:18:15 by takanoraika      ###   ########.fr       */
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

// extern char **environ;
// int main(void)
// {
// 	t_command cmd;
// 	int	bu;
// 	char *args[3];

// 	args[0] = "grep";
// 	args[1] = "a";
// 	args[2] = NULL;
// 	// cmd.filename = "./func_playground/test.txt";
// 	cmd.filename = "test";
// 	// bu = dup(1);
// 	input_redirect_here(cmd);
// 	execve("/usr/bin/grep", args, environ);
// 	return 0;
// }
