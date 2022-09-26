/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:29:24 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:31:35 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cnt_arr(char const *s, char c);
static size_t	strlen_delimiter(char const *s, char c);
static char		**substr_to_arr(char **result, char const *s, char c);
static void		*release_mem(char **result, size_t j);

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		num_arr;

	if (!s)
		return (NULL);
	num_arr = cnt_arr(s, c);
	result = malloc(sizeof(char *) * (num_arr + 1));
	if (!result)
		return (NULL);
	result[num_arr] = NULL;
	return (substr_to_arr(result, s, c));
}

static size_t	cnt_arr(char const *s, char c)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if (s[0] == '\0')
		return (0);
	if (c == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			size++;
		i++;
	}
	if (s[i - 1] != c)
		size++;
	return (size);
}

static char	**substr_to_arr(char **result, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			len = strlen_delimiter(&s[i], c);
			result[j] = ft_substr(s, i, len);
			if (!result[j])
				return (release_mem(result, j));
			j++;
			i += len;
		}
	}
	return (result);
}

static size_t	strlen_delimiter(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*release_mem(char **result, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}
