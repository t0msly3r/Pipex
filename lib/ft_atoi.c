/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:12:43 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/09/22 17:09:10 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	minus;
	int	nbr;

	nbr = 0;
	i = 0;
	minus = 0;
	while ((char)nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((char)nptr[i] == '-')
	{
		minus = 1;
		i++;
	}
	else if ((char)nptr[i] == '+')
		i++;
	while (ft_isdigit((int)nptr[i]))
	{
		nbr *= 10;
		nbr += nptr[i] - '0';
		i++;
	}
	if (minus)
		nbr *= -1;
	return (nbr);
}
