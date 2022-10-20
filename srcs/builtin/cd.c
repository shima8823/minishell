/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:10:54 by shima             #+#    #+#             */
/*   Updated: 2022/10/20 19:55:02 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_home(void);

int	ft_cd(char **args)
{
	if (!args[1])
		return (cd_home());
	if (ft_strlen(args[1]) == 0)
		return (EXIT_SUCCESS);
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	cd_home(void)
{
	ssize_t	env_i;

	env_i = search_var("HOME");
	if (env_i == -1)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(&g_shell.vars[env_i][ft_strlen("HOME") + 1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}