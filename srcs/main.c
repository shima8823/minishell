/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/09/26 10:18:55 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		prompt(void);
int			parse_command(char *line);
bool		is_command(char *input, char *command);
static int	ft_isspace(int c);

int main(int argc, char *argv[])
{
	if (argc != 1)
		return (EXIT_FAILURE);
	printf("hello, minishell\n");
	prompt();
	
	return (EXIT_SUCCESS);
}

void	prompt(void)
{
	char	*line;
	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		printf("cmd_id: %d\n", parse_command(line));
		// printf("%s\n", line);
		free(line);
	}
}

int	parse_command(char *line)
{
	// c
	if (is_command(line, "cd"))
		return (1);
	else if (is_command(line, "pwd"))
		return (2);
	else if (is_command(line, "echo"))
		return (3);
	else if (is_command(line, "exit"))
		exit(EXIT_SUCCESS);
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

static int	ft_isspace(int c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (true);
	return (false);
}