/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:34:14 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/10/01 12:54:13 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*n1;
	char	*n2;

	i = 0;
	n1 = (char *)s1;
	n2 = (char *)s2;
	while ((i < n))
	{
		if (n1[i] != n2[i])
			return ((unsigned char)n1[i] - (unsigned char)n2[i]);
		i++;
	}
	return (0);
}
