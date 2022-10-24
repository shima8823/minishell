/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:21:57 by shima             #+#    #+#             */
/*   Updated: 2022/10/21 15:57:11 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	cnt_digit(int n);
static char			*tostring(int n, char *result, unsigned int digit);

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	digit;

	digit = cnt_digit(n);
	result = malloc(sizeof(char) * (digit + 1));
	if (!result)
		exit(EXIT_FAILURE);
	return (tostring(n, result + digit, digit));
}

static unsigned int	cnt_digit(int n)
{
	unsigned int	digit;

	if (n == 0)
		return (1);
	digit = 0;
	if (n < 0)
		digit++;
	while (n != 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static char	*tostring(int n, char *result, unsigned int digit)
{
	size_t	i;

	i = 0;
	*result = '\0';
	if (n >= 0)
	{
		while (i < digit)
		{
			*(--result) = '0' + (n % 10);
			n /= 10;
			i++;
		}
	}
	else
	{
		while (i + 1 < digit)
		{
			*(--result) = '0' - (n % 10);
			n /= 10;
			i++;
		}
		*(--result) = '-';
	}
	return (result);
}
