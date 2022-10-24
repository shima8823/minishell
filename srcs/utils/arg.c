/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:57:29 by shima             #+#    #+#             */
/*   Updated: 2022/10/24 11:08:22 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	left_shift_args(char ***args, size_t args_i)
{
	int	num_args;

	num_args = count_args(*args);
	while ((*args)[args_i + 1])
	{
		ft_memmove(&(*args)[args_i], &(*args)[args_i + 1], sizeof(char *));
		args_i++;
	}
	(*args)[num_args - 1] = NULL;
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
