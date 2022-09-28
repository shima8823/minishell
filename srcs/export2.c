/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:23:48 by takanoraika       #+#    #+#             */
/*   Updated: 2022/09/28 15:14:03 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_in_export(char *arg, int err_type);

char	*arrange_arg(char *arg)
{
	size_t	i;
	size_t	len;
	bool	is_add_doublequote;
	char	*arranged_arg;

	is_add_doublequote = false;
	len = ft_strlen(arg);
	if (ft_strchr(arg, '=') == NULL)
		return (arg);
	if (arg[0] == '"' && arg[len - 1] == '"')
	{
		arg ++;
		arg[len - 1] = '\0';
	}
	arranged_arg = ft_calloc(len + 3, sizeof(char));
	if (arranged_arg == NULL)
		error_in_export(NULL, 2);
	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		arranged_arg[i] = arg[i];
		i ++;
	}
	if (arg[i] != '=')
	{
		printf("%zu\n",ft_strlen(arranged_arg));
		printf("arranged_arg == %s\n", arranged_arg);
		arranged_arg[i] = '\0';
		return (arranged_arg);
	}
	// printf("%s\n", arranged_arg);
	arranged_arg[i] = arg[i];
	i ++;
	// printf("%s\n", arg);
	// printf("arg[i] == %c, arg[len - 1] == %c\n", arg[i], arg[len - 1]);
	if (arg[i] != '"' && arg[len - 1] != '"')
	{
		printf("add_double_quote...\n");
		is_add_doublequote = true;
		arranged_arg[i] = '"';
		arranged_arg ++;
	}
	// printf("%s\n", arg);
	while (arg[i] != '\0')
	{
		// printf("arg[i] == %c, arranged_arg[i] == %c\n", arg[i], arranged_arg[i]);
		arranged_arg[i] = arg[i];
		i ++;
	}
	if (is_add_doublequote)
	{
		arranged_arg[i] = '"';
		i ++;
		arranged_arg[i] = '\0';
		arranged_arg --;
		printf("arranged_arg == %s\n", arranged_arg);
		return (arranged_arg);
	}
	arranged_arg[i] = '\0';
	printf("arranged_arg == %s\n", arranged_arg);
	return (arranged_arg);
}
