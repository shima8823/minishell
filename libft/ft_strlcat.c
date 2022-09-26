/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:49:30 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:31:59 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	if (dst_len > dstsize)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (i + dst_len + 1 < dstsize && src[i])
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (dst_len + ft_strlen(src));
}
