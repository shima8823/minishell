/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:49:08 by shima             #+#    #+#             */
/*   Updated: 2022/10/15 14:41:16 by shima            ###   ########.fr       */
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

	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	if (node->type == NODE_PIPE)
		printf("PIPE %d\n", node->pipe_index);
	else if (node->type == NODE_COMMAND)
	{
		printf("ARGS: {");
		if (node->command.args)
		{
			i = 0;
			while (node->command.args[i])
			{
				printf("[%s] ", node->command.args[i]);
				i++;
			}
		}
		else
			printf("NULL");
		printf("} ");
		printf("REDIRECTS: {");
		if (node->command.redirects)
		{
			while (node->command.redirects)
			{
				printf("['%s', '%s'] ", node->command.redirects->io_redirect, node->command.redirects->filename);
				node->command.redirects = node->command.redirects->next;
			}
		}
		else
			printf("NULL");
		printf("}\n");
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
