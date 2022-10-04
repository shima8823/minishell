/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:02:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/04 14:55:21 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

bool	parser_pipe(t_ast **node, t_token **token);
bool	parser_command(t_ast **node, t_token **token);
bool	parser_simple_command(t_ast **node, t_token **token);

// node
t_ast	*node_new(char *args, t_node_type type);

bool	parser(t_ast **node, t_token **token)
{
	bool	ret;
	*node = NULL;
	ret = parser_pipe(node, token);
	if (DEBUG)
		print_ast(*node);
	return (ret);
}

bool	parser_pipe(t_ast **node, t_token **token)
{
	t_ast	*left;
	t_ast	*right;

	right = NULL;
	if (!parser_command(node, token))
		return (false);
	while (*token && (*token)->type == CHAR_PIPE)
	{
		*token = (*token)->next;
		if (!parser_command(&right, token))
			return (false);
		left = *node;
		*node = node_new(NULL, NODE_PIPE);
		(*node)->right = right;
		(*node)->left = left;
		right = NULL;
	}
	return (true);
}

bool	parser_command(t_ast **node, t_token **token)
{
	if (!parser_simple_command(node, token))
		return (false);
	return (true);
}

bool	parser_simple_command(t_ast **node, t_token **token)
{
	char	*tmp;

	while (*token && (*token)->type == TOKEN)
	{
		if (!(*node))
		{
			*node = node_new((*token)->data, NODE_WORD);
			*token = (*token)->next;
			continue ;
		}
		tmp = (*node)->args;
		(*node)->args = ft_strjoin((*node)->args, (*token)->data);
		if (!((*node)->args))
		{
			perror("ft_strjoin");
			exit(EXIT_FAILURE);
		}
		free(tmp);
		*token = (*token)->next;
	}
	return (true);
}

t_ast	*node_new(char *args, t_node_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (!args)
		new->args = NULL;
	else
	{
		new->args = ft_strdup(args);
		if (!(new->args))
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
	}
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}