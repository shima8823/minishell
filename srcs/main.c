/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/10/19 20:39:47 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/expansion.h"

void		prompt(void);
int			parse_command(char **args);
bool		is_command(char *input, char *command);
char		**split_line(char *line);

int main(int argc, char *argv[])
{
	extern char **environ;

	if (argc != 1)
		return (EXIT_FAILURE);
	g_shell.vars = environ;
	g_shell.status = 0;
	while (g_shell.vars[g_shell.vars_len])
		g_shell.vars_len++;
	g_shell.backup_fd[0] = 0;
	printf("hello, minishell\n");
	set_signal_init();
	prompt();
	
	return (EXIT_SUCCESS);
}

void	prompt(void)
{
	char	*line;
	char	**args;
	int		status;
	t_token	*token;
	t_ast	*node;

	while (line)
	{
		g_shell.read_fd = 0;
		node = NULL;
		line = readline("minishell > ");
		if (!line)
		{
			ft_putstr_fd("\033[1A", STDERR_FILENO);
			ft_putstr_fd("\033[12C", STDERR_FILENO);
			ft_putendl_fd("exit", STDERR_FILENO);
			exit(EXIT_SUCCESS);
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
		if (status == 4)
			break ;
	}
}

void	error_exit(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}