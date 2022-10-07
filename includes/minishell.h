/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:30 by shima             #+#    #+#             */
/*   Updated: 2022/10/07 18:45:51 by takanoraika      ###   ########.fr       */
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

t_shell	g_shell;

void	signal_set(void);
void	ft_export(char **args);
int		ft_echo(char **args);
int		ft_isspace(int c);
int		search_var(char *name);
char	*return_name(char *var);
int		execution(t_ast node);

#endif