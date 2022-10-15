/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/14 16:19:26 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int	exec(char **args);
static void	exec_in_child(char **args);
static void wait_child(void);

int	execution(t_ast *node)
{
	if (!node)
		return (EXIT_FAILURE);
	if (node->left != NULL)
		execution(node->left);
	if (node->right != NULL)
		execution(node->right);
	if (node->type == NODE_WORD)
		return exec(node->command.args);
	return (EXIT_SUCCESS);
}

static int	exec(char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (EXIT_FAILURE);
	if (builtin_check_and_run(args) == EXIT_FAILURE)
		exec_in_child(args);
	return (EXIT_SUCCESS);
}

static void	exec_in_child(char **args)
{
	if ((g_shell.pid = fork()) < 0)
	{
		put_error(strerror(errno), NULL);
		return ;
	}
	if (g_shell.pid == 0)
	{
		set_signal(SIG_DFL);
		bin_check_and_run(args);
	}
	if (g_shell.pid  > 0)
		wait_child();
}

static void wait_child(void)
{
	int	status;
	int	signal;

	waitpid(g_shell.pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
	}
}
