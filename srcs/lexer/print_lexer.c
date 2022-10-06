/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:05:46 by shima             #+#    #+#             */
/*   Updated: 2022/10/05 17:58:26 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

void print_lexer(t_lexer *lexer_buf)
{
	char	*type;
	t_token	*lst;

	type = NULL;
	printf("===========lexer===========\n");
	lst = lexer_buf->list_tokens;
	while (lst)
	{
		if (lst->type == CHAR_PIPE)
			type = "PIPE";
		else if (lst->type == CHAR_GREATER)
			type = "GREATER";
		else if (lst->type == CHAR_LESSER)
			type = "LESSER";
		else if (lst->type == D_GREATER)
			type = "D_GREATER";
		else if (lst->type == D_LESSER)
			type = "D_LESSER";
		else if (lst->type == TOKEN)
			type = "TOKEN";
		printf("{[%s], %s}\n", lst->data, type);
		lst = lst->next;
	}
	printf("===========================\n");
}
