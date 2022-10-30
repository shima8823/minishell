/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/10/30 13:13:32 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/expansion.h"

static void	init_shell(void);
static void	prompt(void);
static bool	create_node(char *line, t_token **token, t_ast **node);
static void	free_structs(char *line, t_token *token, t_ast *node);

int	main(int argc, char *argv[])
{
	(void) argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	printf("hello, minishell\n");
	init_shell();
	prompt();
	return (g_shell.status);
}

static void	init_shell(void)
{
	extern char	**environ;
	size_t		i;

	g_shell.status = 0;
	while (environ[g_shell.vars_len])
		g_shell.vars_len++;
	g_shell.vars = ft_wcalloc(g_shell.vars_len + 1, sizeof(char *));
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
	t_token	*token;
	t_ast	*node;

	while (1)
	{
		set_signal_init();
		g_shell.old_read_pipe_fd = 0;
		g_shell.cmd_len = 0;
		line = readline("minishell > ");
		if (!line)
			eof_handler();
		if (ft_strlen(line) > MAX_LINE_LEN)
		{
			ft_putendl_fd("minishell:line is too long", STDERR_FILENO);
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		if (!create_node(line, &token, &node))
			continue ;
		execution(node);
		free_structs(line, token, node);
	}
}

static bool	create_node(char *line, t_token **token, t_ast **node)
{
	if (!lexer(token, line))
	{
		free_structs(line, *token, NULL);
		return (false);
	}
	if (!parser(node, *token) || !expansion(node))
	{
		free_structs(line, *token, *node);
		return (false);
	}
	return (true);
}

static void	free_structs(char *line, t_token *token, t_ast *node)
{
	if (line)
		free(line);
	if (token)
		free_tokens(token);
	if (node)
		free_ast(node);
}
