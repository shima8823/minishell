/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 11:03:15 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/expansion.h"

static void		init_shell(void);
static void		prompt(void);

int main(int argc, char *argv[])
{
	if (argc != 1)
		return (EXIT_FAILURE);
	printf("hello, minishell\n");
	init_shell();
	prompt();
	return (EXIT_SUCCESS);
}

static	void	init_shell(void)
{
	extern char	**environ;
	size_t		i;

	g_shell.status = 0;
	while (environ[g_shell.vars_len])
		g_shell.vars_len++;
	g_shell.vars = ft_wcalloc(g_shell.vars_len + 1, sizeof(char*));
	i = 0;
	while (environ[i])
	{
		g_shell.vars[i] = ft_strdup(environ[i]);
		i ++;
	}
	g_shell.vars[i] = NULL;
	g_shell.backup_fd[0] = 0;
}

static void	prompt(void)
{
	char	*line;
	char	**args;
	int		status;
	t_token	*token;
	t_ast	*node;

	while (line)
	{
		set_signal_init();
		g_shell.old_read_pipe_fd = 0;
		g_shell.cmd_len = 0;
		node = NULL;
		line = readline("minishell > ");
		if (!line)
		{
			ft_putstr_fd("\033[1A", STDERR_FILENO);
			ft_putstr_fd("\033[12C", STDERR_FILENO);
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (*line)
			add_history(line);
		if (!lexer(&token, line))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		if (!parser(&node, token) || !expansion(&node))
		{
			free_tokens(token);
			free_ast(node);
			free(line);
			continue;
		}
		status = execution(node);
		free_tokens(token);
		free_ast(node);
		free(line);
	}
}

void	error_exit(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}