/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:17:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:27:13 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_redirect_here(t_command cmd)
{
	char	*line;
	char	*res;
	char	*tmp;
	int		fd[2];

	set_signal_here();
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	res = malloc(1);
	if (!res)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (ft_strncmp(cmd.redirects->filename, line, \
		ft_strlen(cmd.redirects->filename)) == 0)
		{
			free(line);
			break ;
		}
		tmp = line;
		line = ft_strjoin(line, "\n");
		if (!line)
			exit(EXIT_FAILURE);
		if (tmp)
			free(tmp);
		tmp = res;
		res = ft_strjoin(res, line);
		if (!res)
			exit(EXIT_FAILURE);
		if (tmp)
			free(tmp);
		free(line);
	}
	ft_putstr_fd(res, fd[PIPE_WRITE]);
	dup2(fd[PIPE_READ], STDIN_FILENO);
	wclose(fd[PIPE_READ]);
	wclose(fd[PIPE_WRITE]);
	free(res);
	return (0);
}
