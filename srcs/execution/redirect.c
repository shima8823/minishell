/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:20:46 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/12 14:44:59 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output_redirect_write(t_command cmd)
{
	int	fd;

	fd = open(cmd.filename, O_WRONLY);
	if (fd == -1)
		return ;
	dup2(STDOUT_FILENO, fd);
	close(fd);
}

void	output_redirect_update(t_command cmd)
{
	int	fd;

	fd = open(cmd.filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return ;
	dup2(STDOUT_FILENO, fd);
	close(fd);
}


extern char **environ;
int main(void)
{
	t_command cmd;
	char *args[2];

	args[0] = "ls";
	args[1] = NULL;
	execve("/bin/ls", args, environ);
	return 0;
}
