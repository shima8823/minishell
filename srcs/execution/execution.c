/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/12 12:15:06 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int	exec(char **args);
static void	exec_in_child(char **args);

int	execution(t_ast *node)
{
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == NODE_PIPE)
		return (1);
	else if (node->type == NODE_REDIRECT)
		return (1);
	else if (node->type == NODE_WORD)
		return exec(node->command.args);
	return (EXIT_SUCCESS);
}

static void	exec_in_child(char **args)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
	{
		put_error(strerror(errno), NULL);
		return ;
	}
	if (pid == 0)
		bin_check_and_run(args);
	if (pid > 0)
		waitpid(pid, NULL, 0);
}

static int	exec(char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (EXIT_FAILURE);
	if (builtin_check_and_run(args) == EXIT_FAILURE)
		exec_in_child(args);
	return (EXIT_SUCCESS);
}
