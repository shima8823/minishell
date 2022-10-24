/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:48:41 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/24 10:17:45 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wdup2(int old_fd, int new_fd)
{
	int	res;

	res = dup2(old_fd, new_fd);
	if (res < 0)
	{
		g_shell.status = -1;
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return (res);
}
