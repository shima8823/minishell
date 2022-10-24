/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:57:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 13:35:11 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

# define QUOTE_ERROR_MSG "minishell: double quote or quote is expected"

typedef enum e_token_type {
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

typedef enum e_token_state {
	STATE_GENERAL,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
}	t_token_state;

typedef struct s_tokenizer_info
{
	size_t			line_size;
	size_t			line_i;
	size_t			data_i;
	t_token_state	state;
	bool			do_skip_quote;
}	t_tokenizer_info;

typedef struct s_token {
	char			*data;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// lexer.c
bool	lexer(t_token **token, char *line);
t_token	*token_new(size_t data_size, t_token_type type);
t_token	*tokenizer(char *line, bool *is_missing_quote, bool do_skip_quote);
void	free_tokens(t_token *token);
int		count_tokens(t_token *token);

// state_general.c
void	state_general(char *line, t_tokenizer_info *info, t_token **lst);

// state_quote.c
void	state_quote(char c, t_tokenizer_info *info, t_token **lst);

// print_lexer.c
void	print_tokens(t_token *token);

#endif