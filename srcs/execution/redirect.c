/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:20:46 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/30 13:17:32 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	judge_redirect(t_command cmd);
int	input_redirect_here(t_command cmd);
int	output_redirect(t_command cmd);
int	output_redirect_append(t_command cmd);
int	input_redirect(t_command cmd);

void	do_redirect(t_command cmd)
{
	while (cmd.redirects)
	{
		if (judge_redirect(cmd) != 0)
		{
			put_error(strerror(errno), cmd.redirects->filename);
			exit(EXIT_FAILURE);
		}
		cmd.redirects = cmd.redirects->next;
	}
}

int	judge_redirect(t_command cmd)
{
	if (ft_strncmp(cmd.redirects->io_redirect, "<", 2) == 0)
		return (input_redirect(cmd));
	else if (ft_strncmp(cmd.redirects->io_redirect, ">", 2) == 0)
		return (output_redirect(cmd));
	else if (ft_strncmp(cmd.redirects->io_redirect, ">>", 3) == 0)
		return (output_redirect_append(cmd));
	else if (ft_strncmp(cmd.redirects->io_redirect, "<<", 3) == 0)
		return (input_redirect_here(cmd));
	return (1);
}

int	output_redirect(t_command cmd)
{
	int	fd;

	fd = wopen(cmd.redirects->filename, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	wdup2(fd, STDOUT_FILENO);
	wclose(fd);
	return (0);
}

int	output_redirect_append(t_command cmd)
{
	int	fd;

	fd = wopen(cmd.redirects->filename, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	wdup2(fd, STDOUT_FILENO);
	wclose(fd);
	return (0);
}

int	input_redirect(t_command cmd)
{
	int	fd;

	fd = wopen(cmd.redirects->filename, O_RDONLY, 0);
	if (fd == -1)
		return (1);
	wdup2(fd, STDIN_FILENO);
	wclose(fd);
	return (0);
}
