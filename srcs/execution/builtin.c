/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:12:09 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/24 10:39:13 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_command(char *input, char *command);

int	builtin_run(t_command cmd, char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (EXIT_FAILURE);
	if (cmd.redirects)
		backup_fd();
	while (cmd.redirects)
	{
		do_redirect(cmd);
		// if (do_redirect(cmd) != 0)
		// {
		// 	put_error(strerror(errno), cmd.redirects->filename);
		// 	return (1);
		// }
		cmd.redirects = cmd.redirects->next;
	}
	return (run_builtin(args));
}

int	run_builtin(char **args)
{
	if (is_command(args[0], "cd"))
		return (ft_cd(args));
	else if (is_command(args[0], "pwd"))
		return (ft_pwd(args));
	else if (is_command(args[0], "echo"))
		return (ft_echo(args));
	else if (is_command(args[0], "exit"))
		return (ft_exit(args));
	else if (is_command(args[0], "export"))
		return (ft_export(args));
	else if (is_command(args[0], "unset"))
		return (ft_unset(args));
	else if (is_command(args[0], "env"))
		return (ft_env(args));
	return (EXIT_FAILURE);
}

bool	is_command_exist_builtin(char **args)
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
