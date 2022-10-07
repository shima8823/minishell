/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/07 18:35:59 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (EXIT_FAILURE);
	if (builtin_check_and_run(args) == -1)
		return (-1);
	if (bin_check_and_run(args) == -1)
		return (-1);
	if (file_check_and_run(args) == -1)
		return (-1);
	return (0);
}

int	execution(t_ast ast)
{
	// while (ast.right != NULL)
	// {
	// }
	if (ast.type == NODE_PIPE)
		return ;
	else if (ast.type == NODE_REDIRECT)
		return ;
	else if (ast.type == NODE_PIPE)
		exec(ast.command.args);
}