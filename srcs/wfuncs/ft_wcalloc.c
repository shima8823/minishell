/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takanoraika <takanoraika@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:42:30 by takanoraika       #+#    #+#             */
/*   Updated: 2022/10/24 10:17:47 by takanoraika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_wcalloc(size_t count, size_t size)
{
	void	*res;

	res = ft_calloc(count, size);
	if (!res)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (res);
}
