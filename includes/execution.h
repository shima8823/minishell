/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:27:12 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 11:22:42 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define PIPE_READ 0
# define PIPE_WRITE 1

int		builtin_check_and_run(char **args);
int		bin_check_and_run(char **args);
void	exec_signal_set(void);
void	run_pipe_in_child(void);

#endif