/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:32:42 by shima             #+#    #+#             */
/*   Updated: 2022/10/15 14:22:52 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "lexer.h"

# define SYNTAX_ERROR_MSG "minishell: syntax error"

typedef enum	e_node_type {
	NODE_PIPE,
	NODE_COMMAND,
}	t_node_type;

// typedef struct s_command
// {
// 	char			**args;
// 	char			*io_redirect;
// 	char			*filename;
// }	t_command;

typedef struct	s_redirect
{
	char				*io_redirect;
	char				*filename;
	struct s_redirect	*prev;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char		**args;
	t_redirect	*redirects;
}	t_command;

typedef struct s_ast
{
	t_command		command;
	t_node_type		type;
	int				pipe_index;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// parser.c
bool	parser(t_ast **node, t_token *token);
int		count_args(char **args);
void	free_ast(t_ast *node);

// print_ast.c
void	print_ast(t_ast *node);

// node.c
t_ast		*node_new(t_node_type type);
void		str_to_new_args(t_ast **cmd_node, const char *str);
t_redirect	*redirect_new(void);

#endif