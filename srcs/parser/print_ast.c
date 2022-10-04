/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:49:08 by shima             #+#    #+#             */
/*   Updated: 2022/10/04 14:54:15 by shima            ###   ########.fr       */
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
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else
		printf("[%s]\n", node->args);
	print_recursive(node->left);
	print_recursive(node->right);
}
/*
echo hello|grep h|less|echo
PIPE
PIPE
PIPE
[echohello]
[greph]
[less]
[echo]

			PIPE
		PIPE	echo
	PIPE	less
eh		greph
*/

