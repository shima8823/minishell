/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:32:42 by shima             #+#    #+#             */
/*   Updated: 2022/10/03 13:11:29 by shima            ###   ########.fr       */
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

// parser.h
bool	parser(t_ast *node);

#endif