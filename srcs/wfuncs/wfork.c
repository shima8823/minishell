/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:40:30 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:41:38 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wfork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		g_shell.status = -1;
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
