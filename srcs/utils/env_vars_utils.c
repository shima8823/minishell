/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:39:38 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 14:54:36 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

ssize_t	search_var(char *name)
{
	char	*res;
	ssize_t	i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (g_shell.vars_len > i)
	{
		if (ft_strncmp(g_shell.vars[i], name, name_len) == 0 && \
			(g_shell.vars[i][name_len] == '\0' || \
			g_shell.vars[i][name_len] == '='))
			return (i);
		i ++;
	}
	return (-1);
}

char	*return_name(char *var)
{
	char	*res;
	size_t	i;

	res = ft_strdup(var);
	i = 0;
	while (res[i] != '=' && res[i] != '\0')
		i++;
	res[i] = '\0';
	return (res);
}
