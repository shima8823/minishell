/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:07:30 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:28:05 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wopen(const char *path, int flag, int mode)
{
	int	fd;

	fd = open(path, flag, mode);
	if (fd < 0)
	{
		perror(path);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
