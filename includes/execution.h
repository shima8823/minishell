/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:27:12 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 12:33:49 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define PIPE_READ 0
# define PIPE_WRITE 1

int		builtin_check_and_run(t_command cmd, char **args);
int		bin_check_and_run(char **args);
void	exec_signal_set(void);
void	run_pipe_in_child(void);
void	do_redirect(t_command cmd);
void	backup_fd(void);
void	restore_fd(void);

#endif