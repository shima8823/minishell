/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:42:03 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:31:26 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	cnt_digit(int n);
static char			*tostring(int n, char *result, unsigned int digit);

void	ft_putnbr_fd(int n, int fd)
{
	char			result[11];
	unsigned int	digit;

	digit = cnt_digit(n);
	write(fd, tostring(n, result + digit, digit), digit);
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
