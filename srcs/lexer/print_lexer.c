/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:05:46 by shima             #+#    #+#             */
/*   Updated: 2022/10/13 14:53:06 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

void print_tokens(t_token *token)
{
	char	*type;

	type = NULL;
	printf("===========lexer===========\n");
	while (token)
	{
		if (token->type == CHAR_PIPE)
			type = "PIPE";
		else if (token->type == CHAR_GREATER)
			type = "GREATER";
		else if (token->type == CHAR_LESSER)
			type = "LESSER";
		else if (token->type == D_GREATER)
			type = "D_GREATER";
		else if (token->type == D_LESSER)
			type = "D_LESSER";
		else if (token->type == TOKEN)
			type = "TOKEN";
		printf("{[%s], %s}\n", token->data, type);
		token = token->next;
	}
	printf("===========================\n");
}
