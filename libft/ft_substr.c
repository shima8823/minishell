/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:07:47 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:32:36 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s <= start)
		start = len_s;
	if (len_s - start < len)
		len = len_s - start;
	ret = malloc(len + 1 * sizeof(char));
	if (ret)
		ft_strlcpy(ret, &s[start], len + 1);
	return (ret);
}
