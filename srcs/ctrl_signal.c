/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:35:27 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/14 13:22:07 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	display_new_line(void)
{
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(int code)
{
	if (code == SIGINT)
	{
		display_new_line();
		if (signal(SIGINT, signal_handler) == SIG_ERR)
		{
			ft_putstr_fd("signal error\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	else if (code == SIGQUIT)
	{
		ft_putstr_fd("\033[12C", STDERR_FILENO);
		if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		{
			ft_putstr_fd("signal error\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
}

void	signal_set(void (*func)(int))
{
	if (signal(SIGINT, func) == SIG_ERR
		|| signal(SIGQUIT, func) == SIG_ERR)
	{
		ft_putstr_fd("signal error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

// int main(int argc, char **argv)
// {
// 	signal_set();
// 	while (1)
// 	;
// 	return 0;
// }
