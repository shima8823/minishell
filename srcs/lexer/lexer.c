/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:50:14 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 10:48:46 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

bool	lexer(t_token **token, char *line)
{
	bool	is_missing_quote;
	bool	ret;

	*token = tokenizer(line, &is_missing_quote, false);
	if (DEBUG)
		print_tokens(*token);
	if (count_tokens(*token) == 1 && !((*token)->data)[0])
		return (false);
	if (is_missing_quote)
	{
		ft_putendl_fd(QUOTE_ERROR_MSG, STDERR_FILENO);
		g_shell.status = 258;
		return (false);
	}
	return (true);
}

t_token	*tokenizer(char *line, bool *is_missing_quote, bool do_skip_quote)
{
	t_tokenizer_info	info;
	t_token				*start;
	t_token				*lst;

	if (!line)
		return (NULL);
	ft_bzero(&info, sizeof(t_tokenizer_info));
	info.line_size = ft_strlen(line);
	info.do_skip_quote = do_skip_quote;
	start = token_new(info.line_size, 0);
	lst = start;
	while (line[info.line_i])
	{
		if (info.state == STATE_GENERAL)
			state_general(line, &info, &lst);
		else if (info.state == STATE_IN_DQUOTE || info.state == STATE_IN_QUOTE)
			state_quote(line[info.line_i], &info, &lst);
		(info.line_i)++;
	}
	lst->data[info.data_i] = '\0';
	if (is_missing_quote && info.state != STATE_GENERAL)
		*is_missing_quote = true;
	return (start);
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

int	count_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->data);
		free(token);
		token = tmp;
	}
}
