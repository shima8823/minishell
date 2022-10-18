/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:56:55 by shima             #+#    #+#             */
/*   Updated: 2022/10/18 19:48:06 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

void	state_quote(char c, t_tokenizer_info *info, t_token **lst)
{
	(*lst)->data[(info->data_i)++] = c;
	if ((info->state == STATE_IN_QUOTE && c == CHAR_QUOTE)
		|| (info->state == STATE_IN_DQUOTE && c == CHAR_DQUOTE))
	{
		if (info->do_skip_quote)
			(info->data_i)--;
		info->state = STATE_GENERAL;
	}
}
