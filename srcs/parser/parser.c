/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:02:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/15 15:09:40 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

bool	parser_pipe(t_ast **node, t_token **token);
bool	parser_command(t_ast **node, t_token **token);
bool	parser_redirect(t_ast **cmd_node, t_redirect **last_redirect, t_token **token);
void	add_pipe_index_to_node(t_ast **node);

bool	is_redirect(t_token_type type);

void	token_data_to_node(t_ast **cmd_node, t_ast **last_cmd_node, t_token **token);
void	add_token_to_args(t_ast **cmd_node, t_token **token);

void	free_ast(t_ast *node);

// parser_test
// ===============
// echo
// echo hello
// echo hello > test
// echo hello > test > test2
// echo hello > test > test2 word
// > test > test2 > test3
// > test > test2 > test3 word
// > test > test2 > test3 word hello
// > test > test2 > test3 word > test4
// > test > test2 > test3 word > test4 echo
// > test > test2 > test3 word > test4 echo  | > test > test2 > test3
// ===============
// echo hello > test
//		>
//		cmd
// ===============
// echo hello > test > test2
//		>
//		>
//		cmd
// ===============
// echo hello| grep h > test
// 		pipe
// 	   /	>
// 	eh	       gh
// ===============
// < ca ac < a
// 			<a
// 		ac
//	<ca
// < test echo hello > test2 > test3


bool	parser(t_ast **node, t_token *token)
{
	bool	ret;

	ret = parser_pipe(node, &token);
	if (!ret)
		if (ft_putendl_fd(SYNTAX_ERROR_MSG, STDERR_FILENO) == -1)
			error_exit("ft_putendl_fd");
	add_pipe_index_to_node(node);
	if (DEBUG)
		print_ast(*node);
	return (ret);
}

bool	parser_pipe(t_ast **node, t_token **token)
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

bool	parser_command(t_ast **node, t_token **token)
{
	t_ast	*cmd_node;
	t_ast	*last_cmd_node;
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

void	token_data_to_node(t_ast **cmd_node, t_ast **last_cmd_node, t_token **token)
{
	t_ast	*left;

	if (!(*cmd_node)->command.args)
	{
		str_to_new_args(cmd_node, (*token)->data);
		*last_cmd_node = *cmd_node;
		return ;
	}
	add_token_to_args(last_cmd_node, token);
}

void	add_token_to_args(t_ast **cmd_node, t_token **token)
{
	char	***args;
	char	**tmp;
	int		num_args;
	int		i;

	args = &((*cmd_node)->command.args);
	tmp = (*cmd_node)->command.args;
	num_args = count_args(*args);
	*args = malloc(sizeof(char *) * (num_args + 2));
	if (!(*args))
		error_exit("malloc");
	i = -1;
	while (++i < num_args)
		(*args)[i] = tmp[i];
	(*args)[i] = ft_strdup((*token)->data);
	if (!(*args)[i])
		error_exit("ft_strdup");
	(*args)[i + 1] = NULL;
	free(tmp);
}

bool	parser_redirect(t_ast **cmd_node, t_redirect **last_redirect, t_token **token)
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
	if (!(redirect->io_redirect))
		error_exit("ft_strdup");
	*last_redirect = redirect;
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type != TOKEN)
		return (false);
	redirect->filename = ft_strdup((*token)->data);
	if (!(redirect->filename))
		error_exit("ft_strdup");
	return (true);
}

bool	is_redirect(t_token_type type)
{
	return (type == CHAR_GREATER
		|| type == CHAR_LESSER
		|| type == D_GREATER
		|| type == D_LESSER);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	add_pipe_index_to_node(t_ast **node)
{
	t_ast	*pipe_node;
	int		pipe_index;

	pipe_index = 0;
	pipe_node = *node;
	while (pipe_node && pipe_node->type == NODE_PIPE)
	{
		pipe_node->pipe_index = ++pipe_index;
		pipe_node = pipe_node->left;
	}
}

void	free_ast(t_ast *node)
{
	t_ast		*left;
	t_ast		*right;
	t_redirect	*tmp;
	int			i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		if (node->command.args)
		{
			i = 0;
			while (node->command.args[i])
			{
				free(node->command.args[i]);
				i++;
			}
			free(node->command.args);
		}
		while (node->command.redirects)
		{
			free(node->command.redirects->io_redirect);
			free(node->command.redirects->filename);
			tmp = node->command.redirects;
			node->command.redirects = node->command.redirects->next;
			free(tmp);
		}
	}
	left = node->left;
	right = node->right;
	free(node);
	free_ast(left);
	free_ast(right);
}
