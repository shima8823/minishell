/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:35:27 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/20 13:41:11 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int code)
{
	g_shell.status = EXIT_FAILURE;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal_init(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("signal error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
void	set_signal(void (*func)(int))
{
	if (signal(SIGINT, func) == SIG_ERR
		|| signal(SIGQUIT, func) == SIG_ERR)
	{
		ft_putstr_fd("signal error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
