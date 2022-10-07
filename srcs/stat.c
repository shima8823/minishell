/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:02:15 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/08 06:59:50 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_executable(const char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (false);
	if ((buf.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	if ((buf.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

bool	is_command_exist(const char *path)
{
	struct stat	buf;

	if (!path)
		return (false);
	if (lstat(path, &buf) == -1)
		return (false);
	if (S_ISDIR(buf.st_mode))
		return (false);
	return (true);
}

bool	is_directory(const char *path)
{
	struct stat buf;

	if (stat(path, &buf) == -1)
		return (false);
	if (S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}