/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/10/08 07:07:24 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		prompt(void);
int			parse_command(char **args);
bool		is_command(char *input, char *command);
char		**split_line(char *line);
void		free_args(char **args);

// lexer
void	print_lexer(t_lexer *lexer_buf);
void	free_lexer(t_lexer *lexer_buf);

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
	t_lexer	*lexer_buf;
	t_ast	*node;
	
	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		args = split_line(line);
		lexer_buf = lexer(line);
		if (!parser(&node, &(lexer_buf->list_tokens)))
			ft_putendl_fd("syntax error", STDERR_FILENO);
		status = execution(node);
		// printf("%s\n", line);
		free_lexer(lexer_buf);
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

void	free_lexer(t_lexer *lexer_buf)
{
	t_token	*lst;
	t_token	*tmp;

	lst = lexer_buf->list_tokens;
	while (lst)
	{
		tmp = lst->next;
		free(lst->data);
		free(lst);
		lst = tmp;
	}
	free(lexer_buf);
}