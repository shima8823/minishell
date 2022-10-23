/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:20:46 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/20 13:06:22 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	input_redirect_here(t_command cmd);
int	output_redirect(t_command cmd);
int	output_redirect_append(t_command cmd);
int	input_redirect(t_command cmd);

int	do_redirect(t_command cmd)
{
	// printf("judge redirect...\n");
	if (ft_strncmp(cmd.redirects->io_redirect, "<", 2) == 0)
	{
		// printf("judge result:input\n");
		return (input_redirect(cmd));
	}
	else if(ft_strncmp(cmd.redirects->io_redirect, ">", 2) == 0)
	{
		// printf("judge result:output\n");
		return (output_redirect(cmd));
	}
	else if(ft_strncmp(cmd.redirects->io_redirect, ">>", 3) == 0)
	{
		// printf("judge result:append\n");
		return (output_redirect_append(cmd));
	}
	else if(ft_strncmp(cmd.redirects->io_redirect, "<<", 3) == 0)
	{
		// printf("judge result:here\n");
		return (input_redirect_here(cmd));
	}
	return (1);
}

int	output_redirect(t_command cmd)
{
	int	fd;

	fd = open(cmd.redirects->filename, O_CREAT | O_WRONLY | O_TRUNC, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	output_redirect_append(t_command cmd)
{
	int	fd;

	fd = open(cmd.redirects->filename, O_WRONLY | O_CREAT | O_APPEND, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	input_redirect(t_command cmd)
{
	int	fd;

	fd = open(cmd.redirects->filename, O_RDONLY);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

