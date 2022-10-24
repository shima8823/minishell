/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:10:33 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 11:17:19 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

void	token_data_to_node(t_ast **cmd_node,
			t_ast **last_cmd_node, t_token **token)
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
	(*args)[i + 1] = NULL;
	free(tmp);
}

bool	is_redirect(t_token_type type)
{
	return (type == CHAR_GREATER
		|| type == CHAR_LESSER
		|| type == D_GREATER
		|| type == D_LESSER);
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
