/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:29:57 by shima             #+#    #+#             */
/*   Updated: 2022/10/30 13:10:13 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **args)
{
	size_t	i;

	(void)args;
	i = 0;
	while (g_shell.vars[i])
	{
		if (ft_strchr(g_shell.vars[i], '='))
			ft_putendl_fd(g_shell.vars[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
