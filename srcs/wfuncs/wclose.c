/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:25:22 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:28:03 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wclose(int fd)
{
	int	res;

	res = close(fd);
	if (res < 0)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	return (res);
}
