/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:34:39 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/09/26 13:43:30 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*a;
	char	cc;

	cc = (char) c;
	i = 0;
	a = (char *)s;
	while (i < n)
	{
		if (a[i] == cc)
			return ((void *)a + i);
		i++;
	}
	return (NULL);
}
