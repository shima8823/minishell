/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:02:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/06 11:57:31 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

bool	parser_pipe(t_ast **node, t_token **token);
bool	parser_command(t_ast **node, t_token **token);
bool	parser_redirect(t_ast **node, t_token **token);

bool	is_redirect(t_token_type type);
int	count_double_arr(char **args);

// node
t_ast	*node_new(const char *str, t_node_type type);

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
		printf("%s, %d\n", __FILE__, __LINE__);
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
	t_ast	*cmd_node;
	char	**tmp;
	int		double_arr_count;
	int		i;

	// pipeの後に何もないなら
	if (!(*token) || (*token)->type == CHAR_PIPE)
		return (false);
	cmd_node = NULL;
	while (*token)
	{
		if ((*token)->type == TOKEN)
		{
			if (!cmd_node)
			{
				printf("%s, %d\n", __FILE__, __LINE__);
				cmd_node = node_new((*token)->data, NODE_WORD);
			}
			else
			{
				printf("%s, %d\n", __FILE__, __LINE__);
				tmp = cmd_node->command.args;
				double_arr_count = count_double_arr(cmd_node->command.args);
				printf("double_arr_count: %d\n", double_arr_count);
				cmd_node->command.args = malloc(sizeof(char *) * (double_arr_count + 2));
				i = 0;
				while (i < double_arr_count)
				{
					(cmd_node->command.args)[i] = ft_strdup(tmp[i]);
					free(tmp[i]);
					i++;
				}
				(cmd_node->command.args)[i] = ft_strdup((*token)->data);
				(cmd_node->command.args)[i + 1] = NULL;
				free(tmp);
			}
		}
		else if (is_redirect((*token)->type))
		{
			if (!parser_redirect(&cmd_node, token))
				return (false);
		}
		else
			break ;
		(*token) = (*token)->next;
	}
	*node = cmd_node;
	printf("%s, %d\n", __FILE__, __LINE__);
	return (true);
}

// echo hello > test
//		>
//		cmd

// echo hello > test > test2
//		>
//		>
//		cmd

// echo hello| grep h > test
// 		pipe
// 	   /	gh
// 	eh	       >

bool	parser_redirect(t_ast **node, t_token **token)
{
	t_ast	*redirect_node;

	redirect_node = node_new((*token)->data, NODE_REDIRECT);
	(*token) = (*token)->next;
	redirect_node->command.filename = ft_strdup((*token)->data);
	redirect_node->left = *node;
	*node = redirect_node;
	return (true);
}

bool	is_redirect(t_token_type type)
{
	return (type == CHAR_GREATER
			|| type == CHAR_LESSER
			|| type == D_GREATER
			|| type == D_LESSER);
}

int	count_double_arr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

t_ast	*node_new(const char *str, t_node_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_bzero(new, sizeof(t_ast));
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	if (!str)
		return (new);
	if (type == NODE_REDIRECT)
		new->command.io_redirect = ft_strdup(str);
	else if (type == NODE_WORD)
	{
		new->command.args = malloc(sizeof(char *) * 2);
		if (!(new->command.args))
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new->command.args[0] = ft_strdup(str);
		new->command.args[1] = NULL;
	}
	return (new);
}