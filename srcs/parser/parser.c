/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:02:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 11:18:32 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

static bool	parser_pipe(t_ast **node, t_token **token);
static bool	parser_command(t_ast **node, t_token **token);
static bool	parser_redirect(t_ast **cmd_node,
				t_redirect **last_redirect, t_token **token);

bool	parser(t_ast **node, t_token *token)
{
	bool	ret;

	ret = parser_pipe(node, &token);
	if (!ret)
	{
		g_shell.status = 258;
		ft_putendl_fd(SYNTAX_ERROR_MSG, STDERR_FILENO);
	}
	add_pipe_index_to_node(node);
	if (DEBUG)
		print_ast(*node);
	return (ret);
}

static bool	parser_pipe(t_ast **node, t_token **token)
{
	t_ast	*left;
	t_ast	*right;

	if (!parser_command(node, token))
		return (false);
	while (*token && (*token)->type == CHAR_PIPE)
	{
		*token = (*token)->next;
		right = NULL;
		if (!parser_command(&right, token))
			return (false);
		left = *node;
		*node = node_new(NODE_PIPE);
		(*node)->right = right;
		(*node)->left = left;
	}
	return (true);
}

static bool	parser_command(t_ast **node, t_token **token)
{
	t_ast		*cmd_node;
	t_ast		*last_cmd_node;
	t_redirect	*last_redirect;

	if (!(*token) || (*token)->type == CHAR_PIPE)
		return (false);
	cmd_node = node_new(NODE_COMMAND);
	last_cmd_node = NULL;
	while (*token)
	{
		if ((*token)->type == TOKEN)
			token_data_to_node(&cmd_node, &last_cmd_node, token);
		else if (is_redirect((*token)->type))
		{
			if (!parser_redirect(&cmd_node, &last_redirect, token))
				return (false);
		}
		else
			break ;
		(*token) = (*token)->next;
	}
	*node = cmd_node;
	return (true);
}

static bool	parser_redirect(t_ast **cmd_node,
				t_redirect **last_redirect, t_token **token)
{
	t_redirect	*redirect;

	redirect = redirect_new();
	if (!((*cmd_node)->command.redirects))
		(*cmd_node)->command.redirects = redirect;
	else
	{
		(*last_redirect)->next = redirect;
		redirect->prev = *last_redirect;
	}
	redirect->io_redirect = ft_strdup((*token)->data);
	*last_redirect = redirect;
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type != TOKEN)
		return (false);
	redirect->filename = ft_strdup((*token)->data);
	return (true);
}
