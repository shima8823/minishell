/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:13 by shima             #+#    #+#             */
/*   Updated: 2022/09/26 17:00:36 by shima            ###   ########.fr       */
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
	signal_set();
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
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		printf("cmd_id: %d\n", parse_command(line));
		// printf("%s\n", line);
		free(line);
	}
}

int	parse_command(char *line)
{
	// return値 -1 = err, 0 = success 1以上はとりあえず
	char	**args;

	args = ft_split(line, ' ');
	if (!args)
	{
		perror("ft_split");
		return (-1);
	}
	if (!(args[0]))
		return (0);
	if (is_command(args[0], "cd"))
		return (1);
	else if (is_command(args[0], "pwd"))
		return (2);
	else if (is_command(args[0], "echo"))
		return (3);
	else if (is_command(args[0], "exit"))
		return (4);
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