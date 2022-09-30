/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:30 by shima             #+#    #+#             */
/*   Updated: 2022/09/30 11:48:16 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_shell {
	char	**vars;
	int		vars_len;
}				t_shell;

t_shell	g_shell;

# define CHAR_GENERAL = -1
# define CHAR_PIPE = '|'
# define CHAR_QOUTE = '\''
# define CHAR_DQUOTE = '\"'
# define CHAR_WHITESPACE = ' '
# define CHAR_GREATER = '>'
# define CHAR_LESSER = '<'
# define CHAR_NULL = '\0'
# define TOKEN = -1

typedef struct s_tok {
	char*	data;
	int		type;
	t_tok*	next;
}	t_tok;

struct s_lexer
{
	t_tok*	llisttok;
	int		ntoks;
}	t_lexer;

void	signal_set(void);
void	ft_export(char **args);
int		ft_echo(char **args);
int		ft_isspace(int c);
int		search_var(char *name);
char	*return_name(char *var);

#endif