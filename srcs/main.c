/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/10/08 12:21:03 by shima            ###   ########.fr       */
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
	if (argc != 1)
		return (EXIT_FAILURE);
	g_shell.vars_len = 0;
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
		if (!parser(&node, lexer_buf->list_tokens))
			ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		status = parse_command(args);
		// printf("%s\n", line);
		free_lexer(lexer_buf);
		free_ast(node);
		free_args(args);
		free(line);
		if (status == 4)
			break ;
	}
}

int	parse_command(char **args)
{
	// return値 -1 = err, 0 = success 1以上はとりあえず
	if (!(args[0]))
		return (0);
	if (is_command(args[0], "cd"))
		return (1);
	else if (is_command(args[0], "pwd"))
		return (2);
	else if (is_command(args[0], "echo"))
		return (ft_echo(args));
	else if (is_command(args[0], "exit"))
		return (4);
	else if (is_command(args[0], "export"))
		ft_export(args);
	return (0);
}

bool	is_command(char *input, char *command)
{
	size_t	i;
	size_t	cmd_len;

	i = 0;
	cmd_len = ft_strlen(command);
	while (ft_isspace(input[i]))
		i++;
	if (ft_strncmp(&input[i], command, cmd_len + 1) == 0)
		return (true);
	return (false);
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

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
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

void	error_exit(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}