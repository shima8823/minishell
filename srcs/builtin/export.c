/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:35:04 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 11:05:34 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*arrange_arg(char *arg);

void	error_in_export(char *arg)
{
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
}

static void	export_vars(void)
{
	size_t	i;

	i = 0;
	while (g_shell.vars_len > i)
	{
		printf("declare -x %s\n", g_shell.vars[i]);
		i++;
	}
}

static int	add_vars(char *arg)
{
	char	*name;
	size_t	i;

	if (arg[0] == '=' || arg == NULL)
		return (-1);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (ft_isspace(arg[i]))
			return (-1);
		i ++;
	}
	name = return_name(arg);
	if (search_var(name) == -1)
		g_shell.vars[g_shell.vars_len - 1] = arrange_arg(arg);
	else
		g_shell.vars[search_var(name)] = arrange_arg(arg);
	free(name);
	return (0);
}

int	ft_export(char **args)
{
	size_t	i;

	if (args[1] == NULL)
	{
		export_vars();
		return (g_shell.status);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (args[i][0] == '"' && args[i][1] == '"')
		{
			error_in_export("");
			g_shell.status = EXIT_FAILURE;
			i++;
			continue ;
		}
		if (add_vars(args[i]) == -1)
			error_in_export(args[i]);
		i ++;
	}
	return (g_shell.status);
}

