/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:39:38 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/24 09:39:22 by shima            ###   ########.fr       */
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
		if (ft_strncmp(g_shell.vars[i], name, name_len) == 0
		&& (g_shell.vars[i][name_len] == '\0' || g_shell.vars[i][name_len] == '='))
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

char	*get_env(char *name)
{
	ssize_t	env_i;

	env_i = search_var(name);
	if (env_i == -1)
		return (NULL);
	if (!ft_strchr(g_shell.vars[env_i], '='))
		return (NULL);
	return (&g_shell.vars[env_i][ft_strlen(name) + 1]);
}
