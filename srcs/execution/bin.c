/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:18 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/19 17:16:35 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static char	*search_bin(char *name);
static int		judge_path(char *name);
static char	**get_splited_path(void);
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

static char	*search_bin(char *name)
{
	int		i;
	char	**splited_path;
	char	*path;

	if (judge_path(name) == 0)
		return (name);
	splited_path = get_splited_path();
	if (splited_path == NULL)
		return (NULL);
	name = ft_strjoin("/", name);
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

static int	judge_path(char *path)
{
	if (path[0] == '.' || path[0] == '/')
		return (0);
	else
		return (-1);
}

static char	**get_splited_path(void)
{
	char	**tmp;
	char	**splited_path;
	int		i;

	i = search_var("PATH");
	if (i == -1)
		return (NULL);
	tmp = ft_split(g_shell.vars[i], '=');
	splited_path = ft_split(tmp[1], ':');
	free_array(tmp);
	return (splited_path);
}

void	put_exec_error(char *path)
{
	if (is_directory(path))
	{
		g_shell.status = 126;
		errno = EISDIR;
	}
	if (is_command_exist(path) && !is_executable(path))
	{
		g_shell.status = 126;
		errno = EACCES;
	}
	if (path[0] != '.' && path[0] != '/')
	{
		g_shell.status = 127;
		put_error(" command not found", path);
		return ;
	}	
	put_error(strerror(errno), path);
	return ;
}