/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/10/14 20:44:59 by shima            ###   ########.fr       */
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
	signal_set();
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
	
	while (true)
	{
		node = NULL;
		line = readline("> ");
		if (!line)
			error_exit("readline");
		args = split_line(line);
		if (!lexer(&token, line))
		{
			free_tokens(token);
			continue ;
		}
		parser(&node, token);
		expansion(&node);
		if (DEBUG)
			print_ast(node);
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