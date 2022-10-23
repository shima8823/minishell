/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:12:09 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 14:25:35 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static bool is_command_exist_builtin(char **args);
bool	is_command(char *input, char *command);

int	builtin_check_and_run(t_command cmd,char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
			return (EXIT_FAILURE);
	if (!is_command_exist_builtin(args))
		return (EXIT_FAILURE);
	if (cmd.redirects)
		backup_fd();
	while (cmd.redirects)
	{
		if(do_redirect(cmd) != 0)
		{
			put_error(strerror(errno), cmd.redirects->filename);
			return (1);
		}
		cmd.redirects = cmd.redirects->next;
	}
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
	else if (is_command(args[0], "print"))
		return (printf("%d\n", g_shell.status));
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
	else if (is_command(args[0], "print"))
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