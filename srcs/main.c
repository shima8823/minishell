/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/10/17 12:15:32 by takanoraika      ###   ########.fr       */
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
	while (g_shell.vars[g_shell.vars_len])
		g_shell.vars_len++;
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
		args = split_line(line);
		if (!lexer(&token, line))
		{
			free_tokens(token);
			continue ;
		}
		if (!parser(&node, token))
			ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		// expansion(&node);
		status = execution(node);
		// printf("%s\n", line);
		free_tokens(token);
		free_ast(node);
		free_array(args);
		free(line);
		if (status == 4)
			break ;
	}
}

char	**split_line(char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	if (!args)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	return (args);
}

void	error_exit(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}