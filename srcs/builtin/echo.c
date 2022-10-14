/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:32:58 by shima             #+#    #+#             */
/*   Updated: 2022/09/27 09:56:01 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool is_option(char *s);

int	ft_echo(char **args)
{
	size_t	i;
	bool	has_option;

	i = 1;
	has_option = is_option(args[1]);
	if (has_option)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	if (!has_option)
		printf("\n");
	return (0);
}

static bool is_option(char *s)
{
	if (!s)
		return (false);
	if (ft_strncmp(s, "-n", 3) == 0)
		return (true);
	return (false);
}
