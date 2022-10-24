/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:10:54 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 09:43:58 by shima            ###   ########.fr       */
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
	char	*value;

	value = get_env("HOME");
	if (!value)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(value) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
