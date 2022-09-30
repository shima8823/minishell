/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:57:28 by shima             #+#    #+#             */
/*   Updated: 2022/09/30 11:57:50 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

#endif