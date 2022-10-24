/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:35:52 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 19:44:17 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cpy_arg_by_equal(char *arg, char **res)
{
	size_t	i;

	i = 0;
	while (arg[i] != '=')
	{
		res[0][i] = arg[i];
		i ++;
	}
	res[0][i] = arg[i];
}

static void	skip_doublequote(char **arg)
{
	size_t	len;
	char	*equal_pnt;

	len = ft_strlen(*arg);
	if (arg[0][0] == '"' && arg[0][len - 1] == '"')
	{
		arg[0][len - 1] = '\0';
		arg[0]++;
	}
	equal_pnt = ft_strchr(*arg, '=');
	if (equal_pnt == NULL)
		return ;
	if (arg[0][0] == '"' && *(equal_pnt - 1) == '"')
	{
		*(equal_pnt - 1) = '\0';
		arg[0]++;
		ft_strlcat(arg[0], equal_pnt, ft_strlen(arg[0]) + ft_strlen(equal_pnt));
	}
}

static void	do_arrange(char *arg, char **res, size_t len)
{
	size_t	i;
	bool	is_dq;

	is_dq = false;
	i = ft_strlen(*res);
	if (arg[i] != '"' && arg[len - 1] != '"')
	{
		is_dq = true;
		res[0][i] = '"';
		res[0]++;
	}
	while (arg[i] != '\0')
	{
		res[0][i] = arg[i];
		i ++;
	}
	if (is_dq)
	{
		res[0][i] = '"';
		i ++;
		res[0][i] = '\0';
		res[0]--;
	}
	else
		res[0][i] = '\0';
}

void	set_var(char *arg, size_t i)
{
	size_t	len;
	char	*res;

	skip_doublequote(&arg);
	len = ft_strlen(arg);
	if (ft_strchr(arg, '=') == NULL)
	{
		g_shell.vars[i] = ft_strdup(arg);
		return ;
	}
	res = ft_wcalloc(len + 3, sizeof(char));
	cpy_arg_by_equal(arg, &res);
	do_arrange(arg, &res, len);
	g_shell.vars[i] = res;
}
