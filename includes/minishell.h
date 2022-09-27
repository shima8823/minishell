/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:20:30 by shima             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/26 18:25:00 by takanoraika      ###   ########.fr       */
=======
/*   Updated: 2022/09/26 21:13:56 by shima            ###   ########.fr       */
>>>>>>> 545183a99c7a4dddcb55d4bb1b0af1df5caa646b
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_shell {
	char	**vars;
	int		vars_len;
}				t_shell;

void	signal_set(void);
void	error_in_export(char *arg);
int		ft_echo(char **args);

#endif