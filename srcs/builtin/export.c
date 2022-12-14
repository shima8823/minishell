/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:35:04 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/24 16:20:46 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*ptr;
	char	*str;

	i = 0;
	while (g_shell.vars_len > i)
	{
		str = ft_strdup(g_shell.vars[i]);
		ptr = ft_strchr(str, '=');
		ft_putstr_fd("declare -x ", 1);
		if (ptr == NULL)
		{
			ft_putendl_fd(str, 1);
			free(str);
			i ++;
			continue ;
		}
		*ptr = '\0';
		ft_putstr_fd(str, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(++ptr, 1);
		ft_putstr_fd("\"\n", 1);
		free(str);
		i++;
	}
}

static void	create_new_vars_and_free_vars(void)
{
	char	**tmp;
	size_t	i;

	g_shell.vars_len ++;
	tmp = ft_wcalloc(g_shell.vars_len + 1, sizeof(char **));
	g_shell.vars[g_shell.vars_len] = NULL;
	i = 0;
	while (g_shell.vars_len > i)
	{
		tmp[i] = g_shell.vars[i];
		i ++;
	}
	free(g_shell.vars);
	g_shell.vars = tmp;
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
