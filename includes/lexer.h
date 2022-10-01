/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:57:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/01 11:18:31 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum	e_char_type {
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '"',
	CHAR_WHITESPACE = ' ',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = '\0',
	TOKEN = -1,
};

enum	e_token_state {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
};

typedef struct s_token {
	char*			data;
	int				type;
	struct s_token*	next;
}	t_token;

typedef struct s_lexer
{
	t_token*	list_tokens;
	int			n_tokens;
}	t_lexer;

// lexer.c
t_lexer	*lexer(char *line);

#endif