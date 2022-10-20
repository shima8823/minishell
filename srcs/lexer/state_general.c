/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:22:08 by shima             #+#    #+#             */
/*   Updated: 2022/10/18 19:41:55 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

static void	general_second_process(
				char *line, t_tokenizer_info *info, t_token **lst);
static void	redirect_process(char *line, t_tokenizer_info *info, t_token **lst);

static void	add_new_token(t_tokenizer_info *info, t_token **lst);
static bool	is_line_finished(char *line, size_t *line_i);

void	state_general(char *line, t_tokenizer_info *info, t_token **lst)
{
	if (line[info->line_i] == CHAR_QUOTE)
	{
		info->state = STATE_IN_QUOTE;
		(*lst)->data[(info->data_i)++] = CHAR_QUOTE;
		if (info->do_skip_quote)
			(info->data_i)--;
		(*lst)->type = TOKEN;
	}
	else if (line[info->line_i] == CHAR_DQUOTE)
	{
		info->state = STATE_IN_DQUOTE;
		(*lst)->data[(info->data_i)++] = CHAR_DQUOTE;
		if (info->do_skip_quote)
			(info->data_i)--;
		(*lst)->type = TOKEN;
	}
	else if (line[info->line_i] == CHAR_WHITESPACE)
	{
		if (info->data_i == 0 || is_line_finished(line, &(info->line_i)))
			return ;
		add_new_token(info, lst);
	}
	else
		general_second_process(line, info, lst);
}

static void	general_second_process(
				char *line, t_tokenizer_info *info, t_token **lst)
{
	if (line[info->line_i] == CHAR_PIPE)
	{
		if (info->data_i > 0)
			add_new_token(info, lst);
		(*lst)->data[(info->data_i)++] = CHAR_PIPE;
		(*lst)->type = CHAR_PIPE;
		if (is_line_finished(line, &(info->line_i)))
			return ;
		add_new_token(info, lst);
	}
	else if (line[info->line_i] == CHAR_GREATER
		|| line[info->line_i] == CHAR_LESSER)
		redirect_process(line, info, lst);
	else
	{
		(*lst)->data[(info->data_i)++] = line[info->line_i];
		(*lst)->type = TOKEN;
	}
}

static void	redirect_process(char *line, t_tokenizer_info *info, t_token **lst)
{
	if (info->data_i > 0)
		add_new_token(info, lst);
	(*lst)->data[(info->data_i)++] = line[info->line_i];
	(*lst)->type = line[info->line_i];
	if (line[info->line_i] == line[info->line_i + 1])
	{
		(*lst)->data[(info->data_i)++] = line[info->line_i];
		if (line[info->line_i] == CHAR_GREATER)
			(*lst)->type = D_GREATER;
		else
			(*lst)->type = D_LESSER;
		(info->line_i)++;
	}
	if (is_line_finished(line, &(info->line_i)))
		return ;
	add_new_token(info, lst);
}

static void	add_new_token(t_tokenizer_info *info, t_token **lst)
{
	(*lst)->data[info->data_i] = '\0';
	(*lst)->next = token_new(info->line_size - info->line_i, 0);
	*lst = (*lst)->next;
	info->data_i = 0;
}

static bool	is_line_finished(char *line, size_t *line_i)
{
	while (line[(*line_i) + 1] == ' ')
		(*line_i)++;
	if (line[(*line_i) + 1] == '\0')
		return (true);
	return (false);
}
