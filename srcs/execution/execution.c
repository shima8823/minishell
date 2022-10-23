/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 14:52:56 by takanoraika      ###   ########.fr       */
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
	size_t	i;

	i = 0;
	if (g_shell.pipe_len > 0)
	{
		if (pipe(g_shell.pipe_fd) == -1)
		{
			put_error(strerror(errno), NULL);
			g_shell.status = -1;
			return ;
		}
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
			close(g_shell.old_read_pipe_fd);
		close(g_shell.pipe_fd[PIPE_WRITE]);
		g_shell.old_read_pipe_fd = g_shell.pipe_fd[PIPE_READ];
	}
}

static void	exec_in_child(t_command cmd, char **args)
{
	size_t	i;

	i = 0;
	g_shell.pid[g_shell.cmd_len] = fork();
	if (g_shell.pid[g_shell.cmd_len] < 0)
	{
		put_error(strerror(errno), NULL);
		g_shell.status = -1;
		return ;
	}
	if (g_shell.pid[g_shell.cmd_len] == 0)
	{
		set_signal(SIG_DFL);
		while (cmd.redirects)
		{
			if (do_redirect(cmd) != 0)
			{
				put_error(strerror(errno), cmd.redirects->filename);
				exit(EXIT_FAILURE);
			}
			cmd.redirects = cmd.redirects->next;
		}
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

	if (waitpid(g_shell.pid[i], &status, 0) == -1)
	{
		perror("waitpid");
		return ;
	}
	if (WIFEXITED(status))
		g_shell.status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		if (signal == SIGINT)
			ft_putendl_fd("", STDERR_FILENO);
		g_shell.status = signal + 128;
	}
}
