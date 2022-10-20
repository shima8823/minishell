/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:00:38 by shima             #+#    #+#             */
/*   Updated: 2022/10/18 19:35:36 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include <stdlib.h>
#include <stdbool.h>

#define AMBIGUOUS_MSG "minishell: ambiguous redirect"

// expansion.c
bool	expansion(t_ast **node);

// expand.c
void	expand_filename(t_redirect **cmd_redirect, bool *is_ambiguous_redirect);
void	expand_args(char ***args);

// expand_str.c
char	*expand_str(char *s);

#endif