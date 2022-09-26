/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:35:27 by takanoraika       #+#    #+#             */
/*   Updated: 2022/09/26 15:01:32 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int code)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	if (code == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		if (sigaction(SIGINT, &sa, NULL) < 0)
			printf("sigacation error\n");
	}
}

void	signal_set(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		printf("sigacation error\n");
}

// int main(int argc, char **argv)
// {
// 	signal_set();
// 	while (1)
// 	;
// 	return 0;
// }
