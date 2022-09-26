/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:43:46 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:32:30 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	last = ft_strlen(s1);
	first = 0;
	while (s1[first])
	{
		if (!(ft_strchr(set, s1[first])))
			break ;
		first++;
	}
	if (first == last)
		return (ft_strdup(""));
	while (last--)
	{
		if (!(ft_strchr(set, s1[last])))
			break ;
	}
	return (ft_substr(s1, first, last - first + 1));
}
