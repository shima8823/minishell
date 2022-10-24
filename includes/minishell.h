/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:30 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 13:12:05 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>  
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "execution.h"
# include "wfuncs.h"

#ifndef DEBUG
# define DEBUG	0
#endif

typedef struct s_shell {
	char	**vars;
	size_t	vars_len;
	size_t	cmd_len;
	ssize_t	pipe_len;
	int		old_read_pipe_fd;
	int		pipe_fd[2];
	int		backup_fd[2];
	int		status;
	pid_t	pid[4096];
}				t_shell;

t_shell	g_shell;

// builtin
int		ft_echo(char **args);
int		ft_export(char **args);
int		ft_pwd(char **args);
int		ft_cd(char **args);
int		ft_unset(char **args);
int		ft_env(char **args);
int		ft_exit(char **args);

void	set_signal(void (*func)(int));
void	set_signal_init(void);
void	eof_handler(void);
int		ft_isspace(int c);
ssize_t	search_var(char *name);
void	set_var(char *arg, size_t i);
char	*return_name(char *var);
int		execution(t_ast *node);
void	error_exit(const char *s);
void	free_array(char **array);
bool	is_directory(const char *path);
bool	is_command_exist(const char *path);
bool	is_directory(const char *path);
bool	is_executable(const char *path);
void	put_error(char *msg, char *cmd);
void	left_shift_args(char ***args, size_t args_i);
char	*get_env(char *name);

#endif