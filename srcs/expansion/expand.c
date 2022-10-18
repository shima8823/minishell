/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:34:07 by shima             #+#    #+#             */
/*   Updated: 2022/10/18 19:35:57 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

static void	shift_args(char ***args, size_t args_i);
static void	add_increased_tokens_to_args(char ***args, int num_tokens, t_token **token, size_t args_i);

void	expand_filename(t_redirect **cmd_redirect, bool *is_ambiguous_redirect)
{
	t_redirect	*redirect;
	t_token		*token;
	char		*new;
	char		*tmp;
	int			num_tokens;

	redirect = *cmd_redirect;
	while (redirect)
	{
		if (!redirect->filename)
			return ;
		tmp = redirect->filename;
		new = expand_str(redirect->filename);
		token = tokenizer(new, NULL, true);
		free(tmp);
		free(new);
		if (count_tokens(token) > 1)
		{
			*is_ambiguous_redirect = true;
			free_tokens(token);
			return ;
		}
		redirect->filename = ft_strdup(token->data);
		free_tokens(token);
		redirect = redirect->next;
	}
}

void	expand_args(char ***args)
{
	size_t		i;
	char		*new;
	char		*tmp;
	t_token*	token;
	int			num_tokens;

	i = 0;
	while ((*args)[i])
	{
		tmp = (*args)[i];
		new = expand_str((*args)[i]);
		token = tokenizer(new, NULL, true);
		free(new);
		num_tokens = count_tokens(token);
		if (num_tokens == 0)
			shift_args(args, i);
		else if (num_tokens == 1)
			(*args)[i] = ft_strdup(token->data);
		else if (num_tokens > 1)
			add_increased_tokens_to_args(args, num_tokens, &token, i);
		free(tmp);
		free_tokens(token);
		i++;
	}
}

static void	shift_args(char ***args, size_t args_i)
{
	int	num_args;

	num_args = count_args(*args);
	while ((*args)[args_i + 1])
	{
		ft_memmove(&(*args)[args_i], &(*args)[args_i + 1], sizeof(char *));
		args_i++;
	}
	(*args)[num_args - 1] = NULL;
}

static void	add_increased_tokens_to_args(char ***args, int num_tokens, t_token **token, size_t args_i)
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
	free(tmp);
}

