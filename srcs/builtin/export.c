/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:35:04 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 17:21:38 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*arrange_arg(char *arg);

void	error_in_export(char *arg, int err_type)
{
	char	*str;

	if (err_type == 1)
	{
		str = ft_strdup("minishell: export: `");
		ft_strlcat(str, arg, 21 + ft_strlen(arg));
		ft_strlcat(str, "': not a valid identifier\n", ft_strlen(str) + 27);
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	else if (err_type == 2)
	{
		perror("minishell: export: malloc is failed");
		exit(EXIT_FAILURE);
	}
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

	tmp = ft_calloc(g_shell.vars_len, sizeof(char **));
	if (tmp == NULL)
		error_in_export(NULL, 2);
	i = 0;
	while (g_shell.vars_len - 1 > i)
	{
		tmp[i] = g_shell.vars[i];
		i ++;
	}
	free(g_shell.vars);
	g_shell.vars = tmp;
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
	{
		g_shell.vars_len ++;
		create_new_vars_and_free_vars();
		g_shell.vars[g_shell.vars_len - 1] = arrange_arg(arg);
	}
	else
		g_shell.vars[search_var(name)] = arrange_arg(arg);
	free(name);
	return (0);
}

void	ft_export(char **args)
{
	size_t	i;

	if (args[1] == NULL)
	{
		export_vars();
		return ;
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (args[i][0]=='"' && args[i][1]=='"')
		{
			error_in_export("", 1);
			i++;
			continue ;
		}
		if (add_vars(args[i]) == -1)
			error_in_export(args[i], 1);
		i ++;
	}
}

