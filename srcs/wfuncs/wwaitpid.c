/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wwaitpid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:43:21 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:46:21 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wwaitpid(pid_t pid, int *status, int option)
{
	int	res;

	res = waitpid(pid, status, option);
	if (res < 0)
	{
		g_shell.status = -1;
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	return (res);
}