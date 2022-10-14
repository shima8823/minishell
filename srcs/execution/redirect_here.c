/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:17:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/14 12:18:05 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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