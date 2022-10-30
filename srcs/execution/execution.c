/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/30 13:19:18 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec(t_ast *node, char **args);
static void	exec_in_child(t_command cmd, char **args);
static void	wait_child(size_t i);

int	execution(t_ast *node)
{
	set_signal(SIG_IGN);
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == NODE_PIPE)
		g_shell.pipe_len = node->pipe_index + 1;
	if (node->type == NODE_COMMAND)
	{
		exec(node, node->command.args);
		g_shell.cmd_len ++;
	}
	if (node->left != NULL)
		execution(node->left);
	if (node->right != NULL)
		execution(node->right);
	return (EXIT_SUCCESS);
}

static void	exec(t_ast *node, char **args)
{
	if (g_shell.pipe_len > 0)
	{
		wpipe(g_shell.pipe_fd);
		exec_in_child(node->command, args);
	}
	else
	{
		if (is_command_exist_builtin(args))
			g_shell.status = builtin_run(node->command, args);
		else
			exec_in_child(node->command, args);
	}
	if (g_shell.backup_fd[PIPE_READ] != 0)
		restore_fd();
	if (g_shell.pipe_len > 0)
	{
		g_shell.pipe_len --;
		if (g_shell.old_read_pipe_fd != 0)
			wclose(g_shell.old_read_pipe_fd);
		wclose(g_shell.pipe_fd[PIPE_WRITE]);
		g_shell.old_read_pipe_fd = g_shell.pipe_fd[PIPE_READ];
	}
}

static void	exec_in_child(t_command cmd, char **args)
{
	size_t	i;

	i = 0;
	g_shell.pid[g_shell.cmd_len] = wfork();
	if (g_shell.pid[g_shell.cmd_len] == 0)
	{
		set_signal(SIG_DFL);
		do_redirect(cmd);
		if (!args || !args[0] || args[0][0] == '\0')
			exit(EXIT_FAILURE);
		if (g_shell.pipe_len > 0)
			run_pipe_in_child();
		if (is_command_exist_builtin(args))
			exit(run_builtin(args));
		bin_check_and_run(args);
	}
	while (i <= g_shell.cmd_len && g_shell.pipe_len <= 1)
	{
		wait_child(i);
		i ++;
	}
}

static void	wait_child(size_t i)
{
	int	status;
	int	signal;

	wwaitpid(g_shell.pid[i], &status, 0);
	if (WIFEXITED(status))
		g_shell.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		if (signal == SIGINT)
			ft_putendl_fd("", STDERR_FILENO);
		g_shell.status = signal + 128;
	}
}
