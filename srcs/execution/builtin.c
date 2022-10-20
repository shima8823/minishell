/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:12:09 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 12:37:57 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static bool is_command_exist_builtin(char **args);
bool	is_command(char *input, char *command);

int	builtin_check_and_run(t_command cmd,char **args)
{
	if (cmd.redirects)
		backup_fd();
	while (cmd.redirects)
	{
		do_redirect(cmd);
		cmd.redirects = cmd.redirects->next;
	}
	// if (!is_command_exist_builtin(args))
	// 	return (EXIT_FAILURE);
	if (is_command(args[0], "cd"))
		return (1);
	else if (is_command(args[0], "pwd"))
		return (2);
	else if (is_command(args[0], "echo"))
		return (ft_echo(args));
	else if (is_command(args[0], "exit"))
		return (4);
	else if (is_command(args[0], "export"))
		ft_export(args);
	else if (is_command(args[0], "unset"))
		return (5);
	else if (is_command(args[0], "env"))
		return (6);
	return (EXIT_FAILURE);
}

static bool is_command_exist_builtin(char **args)
{
	if (is_command(args[0], "cd"))
		return (true);
	else if (is_command(args[0], "pwd"))
		return (true);
	else if (is_command(args[0], "echo"))
		return (true);
	else if (is_command(args[0], "exit"))
		return (true);
	else if (is_command(args[0], "export"))
		return (true);
	else if (is_command(args[0], "unset"))
		return (true);
	else if (is_command(args[0], "env"))
		return (true);
	return (false);
}

bool	is_command(char *input, char *command)
{
	size_t	i;
	size_t	cmd_len;

	i = 0;
	cmd_len = ft_strlen(command);
	if (ft_strncmp(&input[i], command, cmd_len + 1) == 0)
		return (true);
	return (false);
}