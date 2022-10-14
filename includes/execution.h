/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:27:12 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/14 16:17:53 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct s_pipe {
	char			*cmd;
	char			**arg;
	struct s_pipe	*next;
}				t_pipe;

int		builtin_check_and_run(char **args);
int		bin_check_and_run(char **args);
void	exec_signal_set(void);
void	ft_pipe(int read_fd, int fd[2], bool is_next);

#endif