/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:23:48 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 11:05:57 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static char	*malloc_arranged_arg(size_t len)
{
	char	*res;

	res = ft_calloc(len + 3, sizeof(char));
	if (res == NULL)
		exit(EXIT_FAILURE)
	return (res);
}

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

char	*arrange_arg(char *arg)
{
	size_t	len;
	char	*res;

	skip_doublequote(&arg);
	len = ft_strlen(arg);
	if (ft_strchr(arg, '=') == NULL)
		return (ft_strdup(arg));
	res = malloc_arranged_arg(len);
	cpy_arg_by_equal(arg, &res);
	do_arrange(arg, &res, len);
	return (res);
}
