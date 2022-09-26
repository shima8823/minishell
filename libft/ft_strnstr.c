/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:09:40 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:32:21 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	i;

	len_needle = ft_strlen(needle);
	if (len_needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] && i + len_needle <= len)
	{
		if (haystack[i] == needle[0])
			if (ft_strncmp(&haystack[i], needle, len_needle) == 0)
				return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
