/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:49:08 by shima             #+#    #+#             */
/*   Updated: 2022/10/06 13:09:34 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static void	print_recursive(t_ast *node);

void	print_ast(t_ast *node)
{
	printf("===========parse===========\n");
	print_recursive(node);
	printf("===========================\n");
}

static void	print_recursive(t_ast *node)
{
	int	i;

	i = 0;
	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_REDIRECT)
	{
		printf("REDIRECT: ");
		printf("[%s] [%s]\n", node->command.io_redirect, node->command.filename);
	}
	else if (node->type == NODE_WORD)
	{
		printf("WORD: ");
		while (node->command.args[i])
		{
			printf("[%s] ", node->command.args[i]);
			i++;
		}
		printf("\n");
	}
	print_recursive(node->left);
	print_recursive(node->right);
}
/*
echo hello|grep h|less|echo
PIPE
PIPE
PIPE
[echo] [hello]
[grep] [h]
[less]
[echo]

			PIPE
		PIPE	echo
	PIPE	less
eh		greph
*/

// echo hello > test
// 		WORD
// REDICRET
