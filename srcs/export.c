/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:35:04 by takanoraika       #+#    #+#             */
/*   Updated: 2022/09/26 18:24:21 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_shell	g_shell;

static void	export_vars()
{
	int	i;
	
	i = 0;
	while (g_shell.vars[i] != NULL)
	{
		printf("declare -x %s", g_shell.vars[i]);
		i++;
	}
}

static void	vars_cpy_to_strs(char **strs)
{
	
}

static char	*arrange_var(char *arg)
{
	
}

static int	add_vars(char *arg)
{
	char	**tmp;

	tmp = ft_calloc(g_shell.vars_len, sizeof(char **));
	if (tmp == NULL)
	{
		perror("minishell: export: malloc is failed");
		exit(EXIT_FAILURE);
	}
	vars_cpy_to_strs(tmp);
	tmp[g_shell.vars_len - 1] = arrange_var;
	tmp[g_shell.vars_len] = NULL;
	g_shell.vars_len ++;
	return (0);
}

void	command_export(char **args)
{
	int	i;
	int	err_flg;
	int	err_argc;

	err_flg = 0;
	if (args == NULL)
		export_vars();
	while (args[i] != NULL)
	{
		if (add_vars(args[i]) == 1)
		{
			err_flg = 1;
			err_argc = i;
		}
		i ++;
	}
	if (err_flg != 0)
		error_in_export(args[err_argc]);
}
