/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:23:57 by shima             #+#    #+#             */
/*   Updated: 2022/10/21 16:08:54 by shima            ###   ########.fr       */
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
	char	*tmp;
	size_t	start;

	start = (*i)++;
	while (!ft_strchr(delimiter, s[*i]))
		(*i)++;
	substr = ft_substr(s, start, *i - start);
	if (!(*new))
		*new = substr;
	else
	{
		tmp = *new;
		*new = ft_strjoin(*new, substr);
		free(tmp);
		free(substr);
	}
}

static char	*create_env_var_name(const char *s, size_t *i)
{
	size_t	start;
	char	*env_var_name;

	start = ++(*i);
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (ft_isdigit(s[*i]))
		return (ft_strdup(""));
	while (ft_isalnum(s[*i]) || s[*i] == '_')
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
	char	*tmp;
	ssize_t	env_i;
	size_t	env_var_name_len;

	env_var_name = create_env_var_name(s, i);
	// printf("env_var_name: %s\n", env_var_name);
	env_var_name_len = ft_strlen(env_var_name);
	if (env_var_name_len == 0)
	{
		if (!(*new))
			*new = ft_strdup("$");
		else
		{
			tmp = *new;
			*new = ft_strjoin(*new, "$");
			free(tmp);
		}
		free(env_var_name);
		return ;
	}
	else if (ft_strncmp(env_var_name, "?", 2) == 0)
	{
		if (!(*new))
			*new = ft_strdup(ft_itoa(g_shell.status));
		else
		{
			tmp = *new;
			*new = ft_strjoin(*new, ft_itoa(g_shell.status));
			free(tmp);
		}
		free(env_var_name);
		return ;
	}
	env_i = search_var(env_var_name);
	free(env_var_name);
	if (env_i == -1)
		return ;
	if (!(*new))
		*new = ft_strdup("");
	tmp = *new;
	*new = ft_strjoin(*new, &g_shell.vars[env_i][env_var_name_len + 1]);
	free(tmp);
}
