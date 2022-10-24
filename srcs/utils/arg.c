/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:57:29 by shima             #+#    #+#             */
/*   Updated: 2022/10/22 11:00:17 by shima            ###   ########.fr       */
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

