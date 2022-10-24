/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfuncs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:12:27 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 19:45:40 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WFUNCS_H
# define WFUNCS_H

int		wopen(const char *path, int flag, int mode);
int		wclose(int fd);
int		wpipe(int fd[2]);
int		wfork(void);
int		wwaitpid(pid_t pid, int *status, int option);
int		wdup2(int old_fd, int new_fd);
void	*ft_wcalloc(size_t count, size_t size);

#endif