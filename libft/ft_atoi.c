/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:11:29 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 06:29:59 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c);
static long	long_overflow(int sign);

int	ft_atoi(const char *str)
{
	size_t			digit;
	int				sign;
	unsigned long	num;
	size_t			i;

	digit = 0;
	sign = 1;
	num = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i++] - '0';
		if (++digit > 19 || num > __LONG_MAX__)
			return ((int)long_overflow(sign));
	}
	return ((int)num * sign);
}

static int	ft_isspace(int c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (true);
	return (false);
}

static long	long_overflow(int sign)
{
	if (sign < 0)
		return (-(__LONG_MAX__) - 1);
	else
		return (__LONG_MAX__);
}
