/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:49:04 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:31:45 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, const char *src);

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + 1 * sizeof(char));
	if (dst)
		ft_strcpy(dst, s1);
	return (dst);
}

static char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
