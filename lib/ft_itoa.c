/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:13:02 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/10/02 09:39:02 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_i(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	is_neg(int n, int sign)
{
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	return (sign);
}

static void	transform(long num, int size, char *a)
{
	if (num < 0)
		num = -num;
	while (num)
	{
		a[--size] = (num % 10) + '0';
		num = num / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*a;
	int		size;
	int		sign;
	long	num;

	num = n;
	sign = 0;
	sign = is_neg(num, sign);
	size = size_i(num);
	a = malloc(sizeof(char) * (size + 1));
	if (!a)
		return (NULL);
	a[size] = '\0';
	if (num == 0)
	{
		a[0] = '0';
		return (a);
	}
	transform(num, size, a);
	if (sign == -1)
		a[0] = '-';
	return (a);
}
