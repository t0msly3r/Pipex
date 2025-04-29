/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:08:29 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/10/02 17:14:15 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	while (n--)
	{
		*cdest++ = *csrc++;
	}
	return (dest);
}
