/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:05:50 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 12:54:46 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

static char	*create_env_var_name(const char *s, size_t *i);
static bool	expand_empty(char **new, char *env_var_name,
				size_t env_var_name_len);
static bool	expand_question(char **new, char *env_var_name);

void	expand_env_var(char **new, const char *s, size_t *i)
{
	char	*env_var_name;
	char	*tmp;
	char	*value;
	size_t	env_var_name_len;

	env_var_name = create_env_var_name(s, i);
	env_var_name_len = ft_strlen(env_var_name);
	if (expand_empty(new, env_var_name, env_var_name_len)
		|| expand_question(new, env_var_name))
		return ;
	value = get_env(env_var_name);
	free(env_var_name);
	if (!value)
		return ;
	if (!(*new))
		*new = ft_strdup("");
	tmp = *new;
	*new = ft_strjoin(*new, value);
	free(tmp);
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
	return (env_var_name);
}

static bool	expand_empty(char **new, char *env_var_name,
				size_t env_var_name_len)
{
	char	*tmp;

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
		return (true);
	}
	return (false);
}

static bool	expand_question(char **new, char *env_var_name)
{
	char	*status;
	char	*tmp;

	if (ft_strncmp(env_var_name, "?", 2) == 0)
	{
		status = ft_itoa(g_shell.status);
		if (!(*new))
			*new = status;
		else
		{
			tmp = *new;
			*new = ft_strjoin(*new, status);
			free(tmp);
			free(status);
		}
		free(env_var_name);
		return (true);
	}
	return (false);
}
