/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:17:55 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 23:33:11 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_doc(char **res, int fd[2], t_command cmd);

int	input_redirect_here(t_command cmd)
{
	char	*res;
	int		fd[2];

	set_signal_here();
	wpipe(fd);
	res = ft_wcalloc(1, 1);
	here_doc(&res, fd, cmd);
	ft_putstr_fd(res, fd[PIPE_WRITE]);
	wdup2(fd[PIPE_READ], STDIN_FILENO);
	wclose(fd[PIPE_READ]);
	wclose(fd[PIPE_WRITE]);
	free(res);
	return (0);
}

static void	here_doc(char **res, int fd[2], t_command cmd)
{
	char	*tmp;
	char	*line;

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
		if (tmp)
			free(tmp);
		tmp = *res;
		*res = ft_strjoin(*res, line);
		if (tmp)
			free(tmp);
		free(line);
	}
}
