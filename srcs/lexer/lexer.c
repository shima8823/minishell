/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:50:14 by shima             #+#    #+#             */
/*   Updated: 2022/10/09 22:15:25 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

static void	init_buf(t_lexer **buf, size_t line_size);
static void	tokenizer(t_lexer *lexer_buf, char *line, size_t line_size);

t_token	*token_new(size_t data_size, t_token_type type);

bool	lexer(t_lexer **lexer_buf, char *line)
{
	bool	ret;
	size_t	line_size;

	line_size = ft_strlen(line);
	init_buf(lexer_buf, line_size);
	tokenizer(*lexer_buf, line, line_size);
	if (DEBUG)
		print_lexer(*lexer_buf);
	if ((*lexer_buf)->is_missing_quote)
	{
		if (ft_putendl_fd(QUOTE_ERROR_MSG, STDERR_FILENO) == -1)
			error_exit("ft_putendl_fd");
		return (false);
	}
	return (true);
}

static void	tokenizer(t_lexer *lexer_buf, char *line, size_t line_size)
{
	t_tokenizer_info	info;
	t_token				*lst;

	ft_bzero(&info, sizeof(t_tokenizer_info));
	lst = lexer_buf->list_tokens;
	info.line_size = line_size;
	while (line[info.line_i])
	{
		if (info.state == STATE_GENERAL)
			state_general(line, &info, &lst);
		else if (info.state == STATE_IN_DQUOTE || info.state == STATE_IN_QUOTE)
			state_quote(line[info.line_i], &info, &lst);
		(info.line_i)++;
	}
	lst->data[info.data_i] = '\0';
	if (info.state != STATE_GENERAL)
		lexer_buf->is_missing_quote = true;
}

static void	init_buf(t_lexer **buf, size_t line_size)
{
	*buf = malloc(sizeof(t_lexer));
	if (!(*buf))
		error_exit("malloc");
	ft_bzero(*buf, sizeof(t_lexer));
	(*buf)->list_tokens = token_new(line_size, 0);
}

t_token	*token_new(size_t data_size, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		error_exit("malloc");
	new->data = malloc(data_size + 1);
	if (!new->data)
		error_exit("malloc");
	new->type = type;
	new->next = NULL;
	return (new);
}