/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:30 by shima             #+#    #+#             */
/*   Updated: 2022/09/29 10:58:19 by takanoraika      ###   ########.fr       */
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

void	signal_set(void);
void	ft_export(char **args);
int		ft_echo(char **args);
int		ft_isspace(int c);
int		search_var(char *name);
char	*return_name(char *var);

#endif