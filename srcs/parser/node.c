/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:47:53 by shima             #+#    #+#             */
/*   Updated: 2022/10/18 19:44:55 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

t_ast	*node_new(t_node_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		error_exit("malloc");
	ft_bzero(new, sizeof(t_ast));
	new->type = type;
	return (new);
}

void	str_to_new_args(t_ast **cmd_node, const char *str)
{
	(*cmd_node)->command.args = malloc(sizeof(char *) * 2);
	if (!((*cmd_node)->command.args))
		error_exit("malloc");
	(*cmd_node)->command.args[0] = ft_strdup(str);
	(*cmd_node)->command.args[1] = NULL;
}

t_redirect	*redirect_new(void)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		error_exit("malloc");
	ft_bzero(new, sizeof(t_redirect));
	return (new);
}
