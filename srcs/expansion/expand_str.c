/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:23:57 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 12:07:51 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expansion.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

static void	switch_state(t_token_state *state);
static void	substr_to_new(char **new, const char *s,
				const char *delimiter, size_t *i);

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
			continue ;
		}
		if (state == STATE_GENERAL)
			substr_to_new(&new, s, "$\"\'", &i);
		else if (state == STATE_IN_DQUOTE)
			substr_to_new(&new, s, "$\"", &i);
	}
	return (new);
}

static void	switch_state(t_token_state *state)
{
	if (*state == STATE_GENERAL)
		*state = STATE_IN_DQUOTE;
	else if (*state == STATE_IN_DQUOTE)
		*state = STATE_GENERAL;
}

static void	substr_to_new(char **new, const char *s,
				const char *delimiter, size_t *i)
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
