/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:42:27 by shima             #+#    #+#             */
/*   Updated: 2022/10/14 19:52:14 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

void expansion_recursion(t_ast **node);
char	*expand_env_vars(char **s);

void skip_quote(char **s, size_t i);
char	*create_env_var_name(char *s, size_t *i);
void add_single_quote_content_to_new(char **new, char **s, size_t *i, t_token_state state);
int	count_tokens(t_token *token);

void expansion(t_ast **node)
{
	expansion_recursion(node);
	// printf("expansion[%s]\n", g_shell.vars[0]);
}

void expansion_recursion(t_ast **node)
{
	t_token*	token;
	char		*new;
	int			num_tokens;
	int			num_args;
	char		**tmp;
	size_t		j;
	int	i;

	if ((*node) == NULL)
		return ;
	if ((*node)->type == NODE_REDIRECT)
	{
		expand_env_vars(&((*node)->command.filename));
	}
	else if ((*node)->type == NODE_WORD)
	{
		i = 0;
		while ((*node)->command.args[i])
		{

			new = expand_env_vars(&((*node)->command.args[i]));
			token = tokenizer(new, NULL);
			num_tokens = count_tokens(token);
			// printf("num: %d\n", num_tokens);
			// if (num_tokens > 1)
			// {
			// 	// printf("%s, %d\n", __FILE__, __LINE__);
			// 	num_args = count_args((*node)->command.args);
			// 	tmp = (*node)->command.args;
			// 	(*node)->command.args = malloc(sizeof(char *) * (num_args - 1 + num_tokens + 1));
			// 	if (!((*node)->command.args))
			// 		error_exit("malloc");
			// 	j = 0;
			// 	while (j < (num_args - 1))
			// 	{
			// 		(*node)->command.args[j] = tmp[j];
			// 		j++;
			// 	}
			// 	while (j < (num_args - 1 + num_tokens))
			// 	{
			// 		(*node)->command.args[j] = ft_strdup(token->data);
			// 		token = token->next;
			// 		j++;
			// 	}
			// 	(*node)->command.args[j] = NULL;
			// 	// printf("%s, %d\n", __FILE__, __LINE__);
			// }
			i++;
		}
	}
	expansion_recursion(&(*node)->left);
	expansion_recursion(&(*node)->right);
}

char	*expand_env_vars(char **s)
{
	size_t	i;
	size_t	j;
	size_t	start;
	char	*new;
	char	*sub;
	char	*env_var_name;
	char	*env_var_value;
	int		num_tokens;
	int		num_args;
	t_token_state	state;

	i = 0;
	state = STATE_GENERAL;
	new = NULL;
	while ((*s)[i])
	{
		if ((*s)[i] == CHAR_DQUOTE)
		{
			if (state == STATE_GENERAL)
			{
				skip_quote(s, i);
				state = STATE_IN_DQUOTE;
			}
			else if (state == STATE_IN_DQUOTE)
			{
				skip_quote(s, i);
				state = STATE_GENERAL;
				continue;
			}
		}
		else if ((*s)[i] == CHAR_QUOTE && state == STATE_GENERAL)
			add_single_quote_content_to_new(&new, s, &i, state);

		if ((*s)[i] == '$')
		{
			start = i;
			env_var_name = create_env_var_name(*s, &i);
			if (ft_strlen(env_var_name) == 0 && state == STATE_IN_DQUOTE)
			{
				if (!new)
					new = ft_strdup("$");
				else
					new = ft_strjoin(new, "$");
				free(env_var_name);
				continue;
			}
			env_var_value = getenv(env_var_name);
			free(env_var_name);
			// printf("env_var_value: [%s]\n", env_var_value);
			if (!new)
				new = ft_strdup("");
			if (!env_var_value)
				continue ;
			// # e{cho hello} 2
			// # e{ cho hello} 3
			// # {cho hello} 2

			// if (state == STATE_GENERAL)
			// {
			// 	token = tokenizer(env_var_value, NULL);
			// 	// token数える
			// 	num_tokens = count_tokens(token);
			// 	printf("num_tokens: %d\n", num_tokens);
			// 	num_args = count_args(*args);
			// 	printf("num_args: %d\n", num_args);
			// 	if (num_args == 1 && *args[0][0] == '$')
			// 	{
			// 		**args = malloc(sizeof(char *) * (num_tokens + 1));
			// 		j = 0;
			// 		while (token)
			// 		{
			// 			*args[j] = ft_strdup(token->data);
			// 			token = token->next;
			// 			j++;
			// 		}
			// 		*args[j] = NULL;
			// 	}
			// 	else
			// 	{
			// 		if (env_var_value[0] == ' ')
			// 		{
			// 			**args = malloc(sizeof(char *) * (num_args + num_tokens + 1));
			// 			// substr(, 0, )の0は変わる
			// 			sub = ft_substr(*s, 0, start);
			// 			if (!new)
			// 				new = sub;
			// 			else
			// 				new = ft_strjoin(new, sub);
			// 			*args[0] = new;
			// 			j = 1;
			// 			while (token)
			// 			{
			// 				*args[j] = ft_strdup(token->data);
			// 				token = token->next;
			// 				j++;
			// 			}
			// 		}
			// 	}
			// }

				// ENV = apple banana
				// args = ENV
				// args = grape ENV orange NULL
				// args = grape apple banana orange NULL
				// appleからまたみていくexpand_env_vars
				
			new = ft_strjoin(new, env_var_value);
			// printf("new: [%s]\n", new);
		}
		else
		{
			start = i;
			if (state == STATE_GENERAL)
			{
				while (!ft_strchr("$\"\'", (*s)[i]))
					i++;
			}
			else if (state == STATE_IN_DQUOTE)
			{
				while (!ft_strchr("$\"", (*s)[i]))
					i++;
			}
			// printf("i: %zu\n", i);

			sub = ft_substr(*s, start, i - start);
			// printf("substr: [%s]\n", sub);
			if (!new)
				new = sub;
			else
				new = ft_strjoin(new, sub);
		}
	}
	// printf("\nfinish *s: [%s]\n", *s);
	// printf("\nfinishnew: [%s]\n", new);
	*s = new;
	return (new);
}

void skip_quote(char **s, size_t i)
{
	while ((*s)[i + 1])
	{
		(*s)[i] = (*s)[i + 1];
		i++;
	}
	(*s)[i] = '\0';
	// printf("skip_quote *s [%s]\n", *s);
	// printf("i: %zu\n", i);
}

char	*create_env_var_name(char *s, size_t *i)
{
	size_t	start;
	char	*env_var_name;

	start = (*i)++;
	while (!ft_strchr(" $\"\'", s[*i]))
		(*i)++;
	env_var_name = malloc((*i) - start);
	if (!env_var_name)
		error_exit("malloc");
	ft_strlcpy(env_var_name, &(s[start + 1]), (*i) - start);
	// printf("env_var_name: [%s]\n", env_var_name);
	return (env_var_name);
}

void add_single_quote_content_to_new(char **new, char **s, size_t *i, t_token_state state)
{
	char	*substr;
	size_t	start;

	skip_quote(s, *i);
	start = *i;
	while ((*s)[*i] != CHAR_QUOTE)
		(*i)++;
	substr = ft_substr(*s, start, *i - start);
	if (!(*new))
		*new = substr;
	else
		*new = ft_strjoin(*new, substr);
	skip_quote(s, *i);
}

int	count_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}