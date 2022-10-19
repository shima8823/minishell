/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 11:22:19 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int	exec(t_ast *node,char **args);
static void	exec_in_child(t_ast *node, char **args);
static void wait_child(void);

int	execution(t_ast *node)
{
	// printf("read_fd:%d\n", g_shell.read_fd);
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == NODE_PIPE)
	{
		g_shell.pipe_len = node->pipe_index + 1;
	}
	if (node->type == NODE_COMMAND)
		exec(node, node->command.args);
	if (node->left != NULL)
		execution(node->left);
	if (node->right != NULL)
		execution(node->right);
	return (EXIT_SUCCESS);
}

static int	exec(t_ast *node,char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (EXIT_FAILURE);
	if (g_shell.pipe_len > 0)
	{
		if (pipe(g_shell.fd) == -1)
			put_error("PIPE error", NULL);
	}
	if (g_shell.pipe_len > 0)
		exec_in_child(node, args);
	else if (builtin_check_and_run(args) == EXIT_FAILURE)
		exec_in_child(node, args);
	if (g_shell.pipe_len > 0)
	{
		g_shell.pipe_len --;
		if (g_shell.read_fd != 0)
			close(g_shell.read_fd);
		g_shell.read_fd = g_shell.fd[PIPE_READ];
		close(g_shell.fd[PIPE_WRITE]);
	}
	return (EXIT_SUCCESS);
}

static void	exec_in_child(t_ast *node, char **args)
{
	if ((g_shell.pid = fork()) < 0)
	{
		put_error(strerror(errno), NULL);
		return ;
	}
	if (g_shell.pid == 0)
	{
		set_signal(SIG_DFL);
		if (g_shell.pipe_len > 0)
			run_pipe_in_child();
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
