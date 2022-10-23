/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:35:04 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 14:56:05 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*arrange_vars(char *arg, size_t i);

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

static void	create_new_vars_and_free_vars(void)
{
	char	**tmp;
	size_t	i;

	g_shell.vars_len ++;
	tmp = ft_calloc(g_shell.vars_len, sizeof(char **));
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (g_shell.vars_len > i)
	{
		tmp[i] = g_shell.vars[i];
		i ++;
	}
	if (g_shell.is_malloc_vars)
		free(g_shell.vars);
	g_shell.vars = tmp;
	g_shell.is_malloc_vars = true;
	return ;
}

static int	add_vars(char *arg)
{
	char	*name;
	size_t	i;

	if (arg[0] == '=' || arg == NULL || arg[0] == '\0')
		return (-1);
	i = 0;
	while ((arg[i] != '\0' && arg[i] != '='))
	{
		if (ft_isspace(arg[i]))
			return (-1);
		i ++;
	}
	name = return_name(arg);
	if (search_var(name) == -1)
	{
		create_new_vars_and_free_vars();
		set_var(arg, g_shell.vars_len - 1);
	}
	else
		set_var(arg, search_var(name));
	free(name);
	return (0);
}

int	ft_export(char **args)
{
	size_t	i;
	int		status;

	status = 0;
	if (args[1] == NULL)
	{
		export_vars();
		return (status);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (args[i][0] == '"' && args[i][1] == '"')
		{
			error_in_export("");
			status = EXIT_FAILURE;
			i++;
			continue ;
		}
		if (add_vars(args[i]) == -1)
			error_in_export(args[i]);
		i ++;
	}
	return (status);
}
