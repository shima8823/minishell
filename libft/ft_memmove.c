/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:09:40 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:31:10 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*uns_dst;
	const unsigned char	*uns_src;
	size_t				i;

	if (dst == src)
		return (dst);
	uns_dst = (unsigned char *)dst;
	uns_src = (const unsigned char *)src;
	i = 0;
	while (i < len)
	{
		if (dst < src)
			uns_dst[i] = uns_src[i];
		else
			uns_dst[len - 1 - i] = uns_src[len - 1 - i];
		i++;
	}
	return (dst);
}
