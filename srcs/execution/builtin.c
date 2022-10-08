/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:12:09 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/07 20:16:10 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static bool	is_command(char *input, char *command);

int	builtin_check_and_run(char **args)
{
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
	return (EXIT_FAILURE);
}

static bool	is_command(char *input, char *command)
{
	size_t	i;
	size_t	cmd_len;

	i = 0;
	cmd_len = ft_strlen(command);
	if (ft_strncmp(&input[i], command, cmd_len + 1) == 0)
		return (true);
	return (false);
}