/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:00:38 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 12:56:39 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include <stdbool.h>

# define AMBIGUOUS_MSG "minishell: ambiguous redirect"

// expansion.c
bool	expansion(t_ast **node);

// expand.c
void	expand_redirects(t_redirect **cmd_redirect,
			bool *is_ambiguous_redirect);
void	expand_args(char ***args);

// expand_str.c
char	*expand_str(char *s);

// expand_env.c
void	expand_env_var(char **new, const char *s, size_t *i);

#endif