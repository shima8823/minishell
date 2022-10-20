/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:51 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/20 13:21:20 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int	exec(t_ast *node,char **args);
static void	exec_in_child(t_command cmd, char **args);
static void wait_child(void);

int	execution(t_ast *node)
{
	// printf("read_fd:%d\n", g_shell.read_fd);
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == NODE_PIPE)
		g_shell.pipe_len = node->pipe_index + 1;
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
		if (pipe(g_shell.pipe_fd) == -1)
		{
			put_error(strerror(errno), NULL);
			g_shell.status = -1;
			return (EXIT_FAILURE);
		}
		exec_in_child(node->command, args);
	}
	else
	{
		g_shell.status = builtin_check_and_run(node->command, args);
		if (g_shell.status == EXIT_FAILURE)
			exec_in_child(node->command, args);
	} 
	if (g_shell.backup_fd[0] != 0)
		restore_fd();
	if (g_shell.pipe_len > 0)
	{
		g_shell.pipe_len --;
		if (g_shell.read_fd != 0)
			close(g_shell.read_fd);
		g_shell.read_fd = g_shell.pipe_fd[PIPE_READ];
		close(g_shell.pipe_fd[PIPE_WRITE]);
	}
	return (EXIT_SUCCESS);
}

static void	exec_in_child(t_command cmd, char **args)
{
	if ((g_shell.pid = fork()) < 0)
	{
		put_error(strerror(errno), NULL);
		g_shell.status = -1;
		return ;
	}
	if (g_shell.pid == 0)
	{
		while (cmd.redirects)
		{
			if (do_redirect(cmd) != 0)
			{
				put_error(strerror(errno), cmd.redirects->filename);
				g_shell.status = 1;
				return ;
			}
			cmd.redirects = cmd.redirects->next;
		}
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
