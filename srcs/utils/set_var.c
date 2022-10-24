/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:35:52 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/24 11:04:46 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*skip_quote(char *arg)
{
	size_t	i;
	size_t	j;
	char	*res;

	res = ft_wcalloc(ft_strlen(arg) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] != '\"' || arg[i] != '\'')
		{
			res[j] = arg[i];
			j ++;
		}
		i ++;
	}
	return (res);
}

void	set_var(char *arg, size_t i)
{
	free(g_shell.vars[i]);
	g_shell.vars[i] = skip_quote(arg);
}
