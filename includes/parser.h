/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:32:42 by shima             #+#    #+#             */
/*   Updated: 2022/10/04 14:54:56 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "lexer.h"

typedef enum	e_node_type {
	NODE_PIPE,
	NODE_WORD,
}	t_node_type;

typedef struct s_ast
{
	char			*args;
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// parser.c
bool	parser(t_ast **node, t_token **token);

// print_ast.c
void	print_ast(t_ast *node);

#endif