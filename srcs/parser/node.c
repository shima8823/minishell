/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:47:53 by shima             #+#    #+#             */
/*   Updated: 2022/10/07 12:48:24 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static void	str_to_t_command(t_ast **new, const char *str, t_node_type type);

t_ast	*node_new(const char *str, t_node_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		error_exit("malloc");
	ft_bzero(new, sizeof(t_ast));
	new->type = type;
	if (!str)
		return (new);
	str_to_t_command(&new, str, type);
	return (new);
}

static void	str_to_t_command(t_ast **new, const char *str, t_node_type type)
{
	char	*s;

	s = ft_strdup(str);
	if (!s)
		error_exit("ft_strdup");
	if (type == NODE_REDIRECT)
		(*new)->command.io_redirect = s;
	else if (type == NODE_WORD)
	{
		(*new)->command.args = malloc(sizeof(char *) * 2);
		if (!((*new)->command.args))
			error_exit("malloc");
		(*new)->command.args[0] = s;
		(*new)->command.args[1] = NULL;
	}
}
