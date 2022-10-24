/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:18:28 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 13:13:57 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_identifier_valid(char *identifier);
static void	print_error(char *env_var_name);
static void	delete_env(char *env_var_name);

int	ft_unset(char **args)
{
	size_t	i;
	int		ret;

	ret = EXIT_SUCCESS;
	if (!args[1])
		return (ret);
	i = 1;
	while (args[i])
	{
		if (is_identifier_valid(args[i]))
			delete_env(args[i]);
		else
		{
			print_error(args[i]);
			ret = EXIT_FAILURE;
		}
		i++;
	}
	return (ret);
}

static bool	is_identifier_valid(char *identifier)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(identifier[i]) && identifier[i] != '_')
		return (false);
	i++;
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	print_error(char *env_var_name)
{
	ft_putendl_fd("minishell: unset: `", STDERR_FILENO);
	ft_putendl_fd(env_var_name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static void	delete_env(char *env_var_name)
{
	ssize_t	env_i;

	env_i = search_var(env_var_name);
	if (env_i == -1)
		return ;
	left_shift_args(&g_shell.vars, env_i);
	g_shell.vars_len--;
}
