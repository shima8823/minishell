/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:57:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/06 10:15:12 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum	e_token_type {
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '"',
	CHAR_WHITESPACE = ' ',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = '\0',
	D_GREATER = 1,
	D_LESSER = 2,
	TOKEN = -1,
}	t_token_type;

enum	e_token_state {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
};

typedef struct s_token {
	char*			data;
	t_token_type	type;
	struct s_token*	next;
}	t_token;

typedef struct s_lexer
{
	t_token*	list_tokens;
	int			n_tokens;
}	t_lexer;

// lexer.c
t_lexer	*lexer(char *line);

// print_lexer.c
void print_lexer(t_lexer *lexer_buf);

#endif