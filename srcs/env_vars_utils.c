/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:39:38 by takanoraika       #+#    #+#             */
/*   Updated: 2022/09/28 17:17:32 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_var(char *name)
{
	char	*res;
	size_t	i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (g_shell.vars_len > i)
	{
		if (ft_strncmp(g_shell.vars[i], name, name_len) == 0
		&& (g_shell.vars[i][name_len] == '\0' || g_shell.vars[i][name_len] == '='))
			return (g_shell.vars[i]);
		i ++;
	}
	return (NULL);
}

// int main(int ac, char const *av[])
// {
// 	g_shell.vars = ft_calloc(3, sizeof(char **));
// 	g_shell.vars[2] = "test33=test2";
// 	g_shell.vars[0] = "test=test1";
// 	g_shell.vars[1] = "test3=test2";
// 	g_shell.vars_len = 3;
// 	printf("%s\n",search_var("test3"));
// 	printf("%s\n",search_var("test"));
// 	printf("%s\n",search_var("test33"));
// 	return (0);
// }
