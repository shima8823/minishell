/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:35:04 by takanoraika       #+#    #+#             */
/*   Updated: 2022/09/28 13:50:29 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_shell	g_shell;
char	*arrange_arg(char *arg);

void	error_in_export(char *arg, int err_type)
{
	char *str;

	if (err_type == 1)
	{
		str = ft_strdup("minishell: export: `");
		ft_strlcat(str, arg, 21 + ft_strlen(arg));
		ft_strlcat(str, "': not a valid identifier\n", ft_strlen(str) + 27);
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	else if (err_type == 2)
		perror("minishell: export: malloc is failed");
	exit(EXIT_FAILURE);
}

static void	export_vars()
{
	size_t	i;
	
	i = 0;
	while (g_shell.vars[i] != NULL)
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
	while (g_shell.vars[i] != NULL)
	{
		tmp[i] = g_shell.vars[i];
		i ++;
	}
	free(g_shell.vars);
	g_shell.vars = tmp;
}

static int	add_vars(char *arg)
{
	if (arg[0] == '=')
		return (-1);
	create_new_vars_and_free_vars();
	g_shell.vars_len ++;
	arrange_arg(arg);
	g_shell.vars[g_shell.vars_len - 1] = arrange_arg(arg);
	g_shell.vars[g_shell.vars_len] = NULL;
	return (0);
}

void	ft_export(char **args)
{
	size_t	i;
	int		err_flg;
	int		err_argc;

	err_flg = 0;
	if (args == NULL)
	{
		export_vars();
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		if (add_vars(args[i]) == -1)
		{
			err_flg = 1;
			err_argc = i;
		}
		i ++;
	}
	if (err_flg != 0)
		error_in_export(args[err_argc], 1);
}

int main(int ac, char *av[])
{
	g_shell.vars = ft_calloc(3, sizeof(char **));
	g_shell.vars[0] = "test=test1";
	g_shell.vars[1] = "test3=test2";
	g_shell.vars[2] = NULL;
	g_shell.vars_len = 2;
	ft_export(NULL);
	printf("\n");
	ft_export(av);
	printf("\n");
	ft_export(NULL);
	return (0);
}

