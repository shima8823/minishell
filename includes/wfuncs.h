/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfuncs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:12:27 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/23 15:27:42 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WFUNCS_H
# define WFUNCS_H

int	wopen(const char *path, int flag, int mode);
int	wclose(int fd);

#endif