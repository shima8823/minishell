/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:34:07 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 13:42:29 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

static bool	expand_filename(t_redirect *redirect, bool *is_ambiguous_redirect);
static void	add_increased_tokens_to_args(char ***args,
				int num_tokens, t_token **token, size_t args_i);
static void	variables_init(char ***args, int *num_args,
				char ***previous, int num_tokens);

void	expand_redirects(t_redirect **cmd_redirect, bool *is_ambiguous_redirect)
{
	t_redirect	*redirect;

	redirect = *cmd_redirect;
	while (redirect)
	{
		if (!redirect->filename)
			return ;
		if (ft_strncmp("<<", redirect->io_redirect, 3) == 0)
		{
			redirect = redirect->next;
			continue ;
		}
		if (!expand_filename(redirect, is_ambiguous_redirect))
			return ;
		redirect = redirect->next;
	}
}

void	expand_args(char ***args)
{
	size_t		i;
	char		*new;
	char		*tmp;
	t_token		*token;
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
			left_shift_args(args, i);
		else if (num_tokens == 1)
			(*args)[i] = ft_strdup(token->data);
		else if (num_tokens > 1)
			add_increased_tokens_to_args(args, num_tokens, &token, i);
		free(tmp);
		free_tokens(token);
		i++;
	}
}

static bool	expand_filename(t_redirect *redirect, bool *is_ambiguous_redirect)
{
	t_token		*token;
	char		*new;
	char		*tmp;

	tmp = redirect->filename;
	new = expand_str(redirect->filename);
	token = tokenizer(new, NULL, true);
	free(new);
	if (count_tokens(token) != 1)
	{
		*is_ambiguous_redirect = true;
		free_tokens(token);
		return (false);
	}
	redirect->filename = ft_strdup(token->data);
	free(tmp);
	free_tokens(token);
	return (true);
}

static void	add_increased_tokens_to_args(char ***args,
				int num_tokens, t_token **token, size_t args_i)
{
	char	**previous;
	int		num_args;
	size_t	i;
	size_t	j;

	variables_init(args, &num_args, &previous, num_tokens);
	i = -1;
	while (++i < args_i)
		(*args)[i] = previous[i];
	j = i + 1;
	while ((*token))
	{
		(*args)[i++] = ft_strdup((*token)->data);
		*token = (*token)->next;
	}
	while (i < (size_t)num_args + num_tokens - 1)
	{
		(*args)[i] = previous[j];
		i++;
		j++;
	}
	(*args)[i] = NULL;
	free(previous);
}

static void	variables_init(char ***args, int *num_args,
				char ***previous, int num_tokens)
{
	*num_args = count_args(*args);
	*previous = *args;
	*args = malloc(sizeof(char *) * (*num_args - 1 + num_tokens + 1));
	if (!(*args))
		error_exit("malloc");
}
