/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:30:41 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:34:47 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wpipe(int fd[2])
{
	int	res;

	res = pipe(fd);
	if (res < 0)
	{
		g_shell.status = -1;
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (res);
}
