/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:23:57 by shima             #+#    #+#             */
/*   Updated: 2022/10/18 14:54:46 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

static void	expand_env_var(char **new, const char *s, size_t *i);
static void	switch_state(t_token_state *state);
static char	*create_env_var_name(const char *s, size_t *i);
static void	substr_to_new(char **new, const char *s, const char *delimiter, size_t *i);

char	*expand_str(char *s)
{
	size_t			i;
	char			*new;
	t_token_state	state;

	i = 0;
	state = STATE_GENERAL;
	new = NULL;
	while (s[i])
	{
		if (s[i] == CHAR_DQUOTE)
			switch_state(&state);
		else if (s[i] == CHAR_QUOTE && state == STATE_GENERAL)
			substr_to_new(&new, s, "\'", &i);
		else if (s[i] == '$')
		{
			expand_env_var(&new, s, &i);
			continue;
		}
		if (state == STATE_GENERAL)
			substr_to_new(&new, s, "$\"\'", &i);
		else if (state == STATE_IN_DQUOTE)
			substr_to_new(&new, s, "$\"", &i);
	}
	return (new);
}

static void substr_to_new(char **new, const char *s, const char *delimiter, size_t *i)
{
	char	*substr;
	size_t	start;

	start = (*i)++;
	while (!ft_strchr(delimiter, s[*i]))
		(*i)++;
	substr = ft_substr(s, start, *i - start);
	if (!(*new))
		*new = substr;
	else
		*new = ft_strjoin(*new, substr);
}

static char	*create_env_var_name(const char *s, size_t *i)
{
	size_t	start;
	char	*env_var_name;

	start = ++(*i);
	while (!ft_strchr(" $\"\'", s[*i]))
		(*i)++;
	env_var_name = ft_substr(s, start, *i - start);
	// printf("env_var_name: [%s]\n", env_var_name);
	return (env_var_name);
}

static void switch_state(t_token_state *state)
{
	if (*state == STATE_GENERAL)
		*state = STATE_IN_DQUOTE;
	else if (*state == STATE_IN_DQUOTE)
		*state = STATE_GENERAL;
}

static void	expand_env_var(char **new, const char *s, size_t *i)
{
	char	*env_var_name;
	char	*env_var_value;

	env_var_name = create_env_var_name(s, i);
	// printf("env_var_name: %s\n", env_var_name);
	if (ft_strlen(env_var_name) == 0)
	{
		if (!(*new))
			*new = ft_strdup("$");
		else
			*new = ft_strjoin(*new, "$");
		free(env_var_name);
		return ;
	}
	env_var_value = getenv(env_var_name);
	free(env_var_name);
	if (!env_var_value)
		return ;
	if (!(*new))
		*new = ft_strdup("");
	*new = ft_strjoin(*new, env_var_value);
}
