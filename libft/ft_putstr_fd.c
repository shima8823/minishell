/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:34:24 by shima             #+#    #+#             */
/*   Updated: 2022/10/09 21:48:42 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	while (len > INT_MAX)
	{
		if (write(fd, s, INT_MAX) == -1)
			return (-1);
		s += INT_MAX;
		len -= INT_MAX;
	}
	return (write(fd, s, len));
}
