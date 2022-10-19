/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:20:46 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 17:19:20 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	input_redirect_here(t_command cmd);
void	output_redirect(t_command cmd);
void	output_redirect_append(t_command cmd);
void	input_redirect(t_command cmd);

void	do_redirect(t_command cmd)
{
	// printf("judge redirect...\n");
	if (ft_strncmp(cmd.redirects->io_redirect, "<", 2) == 0)
	{
		// printf("judge result:input\n");
		input_redirect(cmd);
	}
	else if(ft_strncmp(cmd.redirects->io_redirect, ">", 2) == 0)
	{
		// printf("judge result:output\n");
		output_redirect(cmd);
	}
	else if(ft_strncmp(cmd.redirects->io_redirect, ">>", 3) == 0)
	{
		// printf("judge result:append\n");
		output_redirect_append(cmd);
	}
	else if(ft_strncmp(cmd.redirects->io_redirect, "<<", 3) == 0)
	{
		// printf("judge result:here\n");
		input_redirect_here(cmd);
	}
}

void	output_redirect(t_command cmd)
{
	int	fd;

	fd = open(cmd.redirects->filename, O_CREAT | O_WRONLY | O_TRUNC, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	output_redirect_append(t_command cmd)
{
	int	fd;

	fd = open(cmd.redirects->filename, O_WRONLY | O_CREAT | O_APPEND, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	input_redirect(t_command cmd)
{
	int	fd;

	fd = open(cmd.redirects->filename, O_RDONLY);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

