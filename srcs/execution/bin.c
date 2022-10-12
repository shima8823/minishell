/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:18 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/12 11:04:57 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
char	*search_bin(char *name);
void	put_exec_error(char *path);

int	bin_check_and_run(char **args)
{
	char	*path;

	path = search_bin(args[0]);
	if (path)
	{
		if (execve(path, args, g_shell.vars) == -1)
			put_exec_error(args[0]);
	}
	else
		put_exec_error(args[0]);
	return (0);
}

char	*search_bin(char *name)
{
	int		i;
	char	**splited_path;
	char	**tmp;
	char	*path;

	if (is_command_exist(name) && !is_directory(name) &&
		is_executable(name))
			return (name);
	i = search_var("PATH");
	if (i == -1)
		return (NULL);
	tmp = ft_split(g_shell.vars[i], '=');
	splited_path = ft_split(tmp[1], ':');
	name = ft_strjoin("/", name);
	free_array(tmp);
	i = 0;
	while (splited_path[i])
	{
		path = ft_strjoin(splited_path[i], name);
		if (is_command_exist(path) && !is_directory(path) &&
			is_executable(path))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free(name);
	free_array(splited_path);
	return (path);
}

void	put_exec_error(char *path)
{
	if (is_directory(path))
		errno = EISDIR;
	if (!is_executable(path))
		errno = EACCES;
	put_error(strerror(errno), path);
	return ;
}