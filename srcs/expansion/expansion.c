/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:42:27 by shima             #+#    #+#             */
/*   Updated: 2022/10/18 15:09:38 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

void expansion_recursion(t_ast **node, bool *is_ambiguous_redirect);
void	expand_filename(t_redirect **cmd_redirect, bool *is_ambiguous_redirect);
void	expand_args(char ***args);
void	add_increased_tokens_to_args(char ***args, int num_tokens, t_token **token, size_t args_i);



bool	expansion(t_ast **node)
{
	bool	is_ambiguous_redirect;
	is_ambiguous_redirect = false;
	expansion_recursion(node, &is_ambiguous_redirect);
	if (is_ambiguous_redirect)
	{
		ft_putendl_fd(AMBIGUOUS_MSG, STDERR_FILENO);
		return (false);
	}
	return (true);
}

void expansion_recursion(t_ast **node, bool *is_ambiguous_redirect)
{
	if ((*node) == NULL)
		return ;
	if ((*node)->type == NODE_COMMAND)
	{
		if ((*node)->command.redirects)
			expand_filename(&(*node)->command.redirects, is_ambiguous_redirect);
		if ((*node)->command.args)
			expand_args(&(*node)->command.args);
	}
	expansion_recursion(&(*node)->left, is_ambiguous_redirect);
	expansion_recursion(&(*node)->right, is_ambiguous_redirect);
}

void	expand_filename(t_redirect **cmd_redirect, bool *is_ambiguous_redirect)
{
	t_redirect	*redirect;
	t_token		*token;
	char		*new;
	int			num_tokens;

	redirect = *cmd_redirect;
	while (redirect)
	{
		if (!redirect->filename)
			return ;
		new = expand_str(redirect->filename);
		token = tokenizer(new, NULL, true);
		if (count_tokens(token) > 1)
		{
			*is_ambiguous_redirect = true;
			return ;
		}
		redirect->filename = ft_strdup(token->data);
		redirect = redirect->next;
	}
}

void	expand_args(char ***args)
{
	size_t		i;
	char		*new;
	t_token*	token;
	int			num_tokens;
	int			num_args;

	i = 0;
	while ((*args)[i])
	{
		new = expand_str((*args)[i]);
		token = tokenizer(new, NULL, true);
		num_tokens = count_tokens(token);
		if (new == NULL)
		{
			num_args = count_args(*args);
			ft_memmove(&(*args)[i], &(*args)[i + 1], sizeof(char *));
			(*args)[num_args - 1] = NULL;
		}
		else if (num_tokens == 1)
			(*args)[i] = ft_strdup(token->data);
		else if (num_tokens > 1)
			add_increased_tokens_to_args(args, num_tokens, &token, i);
		i++;
	}
}

void	add_increased_tokens_to_args(char ***args, int num_tokens, t_token **token, size_t args_i)
{
	char	**tmp;
	int		num_args;
	size_t		i;
	size_t		j;

	num_args = count_args(*args);
	tmp = *args;
	*args = malloc(sizeof(char *) * (num_args - 1 + num_tokens + 1));
	if (!(*args))
		error_exit("malloc");
	i = 0;
	while (i < args_i)
	{
		(*args)[i] = tmp[i];
		i++;
	}
	j = i + 1;
	while ((*token))
	{
		(*args)[i++] = ft_strdup((*token)->data);
		*token = (*token)->next;
	}
	while (i < num_args + num_tokens - 1)
	{
		(*args)[i] = tmp[j];
		i++;
		j++;
	}
	(*args)[i] = NULL;
}

