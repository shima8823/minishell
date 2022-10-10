/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:32:42 by shima             #+#    #+#             */
/*   Updated: 2022/10/09 22:16:51 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "lexer.h"

# define SYNTAX_ERROR_MSG "minishell: syntax error"

typedef enum	e_node_type {
	NODE_PIPE,
	NODE_WORD,
	NODE_REDIRECT,
}	t_node_type;

// typedef struct s_redirect
// {
	
// };


typedef struct s_command
{
	char			**args;
	char			*io_redirect;
	char			*filename;
}	t_command;

typedef struct s_ast
{
	t_command		command;
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// parser.c
bool	parser(t_ast **node, t_token *token);
void	free_ast(t_ast *node);

// print_ast.c
void	print_ast(t_ast *node);

// node.c
t_ast	*node_new(const char *str, t_node_type type);

#endif