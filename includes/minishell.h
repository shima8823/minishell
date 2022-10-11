/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:30 by shima             #+#    #+#             */
/*   Updated: 2022/10/11 13:30:58 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "execution.h"

#ifndef DEBUG
# define DEBUG	0
#endif

typedef struct s_shell {
	char	**vars;
	int		vars_len;
}				t_shell;

typedef struct s_pipe {
	char			*cmd;
	char			**arg;
	struct s_pipe	*next;
}				t_pipe;

t_shell	g_shell;

void	signal_set(void);
void	ft_export(char **args);
int		ft_echo(char **args);
int		ft_isspace(int c);
ssize_t	search_var(char *name);
char	*return_name(char *var);
int		execution(t_ast *node);
void	error_exit(const char *s);
void	free_array(char **array);
bool	is_directory(const char *path);
bool	is_command_exist(const char *path);
bool	is_directory(const char *path);
bool	is_executable(const char *path);
void	put_error(char *msg, char *cmd);

#endif