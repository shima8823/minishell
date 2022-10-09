/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:57:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/09 22:15:37 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>

#define QUOTE_ERROR_MSG "minishell: double quote or quote is expected"

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

typedef enum	e_token_state {
	STATE_GENERAL,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
}	t_token_state;

typedef struct s_tokenizer_info
{
	size_t			line_size;
	size_t			line_i;
	size_t			data_i;
	int				num_tokens;
	t_token_state	state;
}	t_tokenizer_info;


typedef struct s_token {
	char*			data;
	t_token_type	type;
	struct s_token*	next;
}	t_token;

typedef struct s_lexer
{
	t_token*	list_tokens;
	bool		is_missing_quote;
}	t_lexer;

// lexer.c
bool	lexer(t_lexer **lexer_buf, char *line);
t_token	*token_new(size_t data_size, t_token_type type);

// state_general.c
void	state_general(char *line, t_tokenizer_info *info, t_token **lst);

// state_quote.c
void	state_quote(char c, t_tokenizer_info *info, t_token **lst);

// print_lexer.c
void print_lexer(t_lexer *lexer_buf);

#endif