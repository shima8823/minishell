/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:42:27 by shima             #+#    #+#             */
/*   Updated: 2022/10/19 20:11:24 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

void expansion_recursion(t_ast **node, bool *is_ambiguous_redirect);

bool	expansion(t_ast **node)
{
	bool	is_ambiguous_redirect;
	
	is_ambiguous_redirect = false;
	expansion_recursion(node, &is_ambiguous_redirect);
	if (is_ambiguous_redirect)
	{
		ft_putendl_fd(AMBIGUOUS_MSG, STDERR_FILENO);
		return (false);
	}
	return (true);
}

void expansion_recursion(t_ast **node, bool *is_ambiguous_redirect)
{
	if ((*node) == NULL)
		return ;
	if ((*node)->type == NODE_COMMAND)
	{
		if ((*node)->command.redirects)
			expand_filename(&(*node)->command.redirects, is_ambiguous_redirect);
		if ((*node)->command.args)
			expand_args(&(*node)->command.args);
	}
	expansion_recursion(&(*node)->left, is_ambiguous_redirect);
	expansion_recursion(&(*node)->right, is_ambiguous_redirect);
}

