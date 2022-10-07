/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/07 18:50:13 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (EXIT_FAILURE);
	if (builtin_check_and_run(args) == 0)
		return (0);
	else if (bin_check_and_run(args) == -1)
		return (-1);
	else if (file_check_and_run(args) == -1)
		return (-1);
	return (0);
}

int	execution(t_ast node)
{
	// while (ast.right != NULL)
	// {
	// }
	if (node.type == NODE_PIPE)
		return (1);
	else if (node.type == NODE_REDIRECT)
		return (1);
	else if (node.type == NODE_WORD)
		return exec(node.command.args);
	return (0);
}