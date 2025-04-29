/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:43:19 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/10/02 17:14:45 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_length;

	src_length = ft_strlen((char *)src);
	if (size == 0)
		return (src_length);
	if (src_length + 1 < size)
	{
		ft_memcpy(dst, (char *)src, src_length + 1);
	}
	else
	{
		ft_memcpy(dst, (char *)src, size - 1);
		dst[size - 1] = '\0';
	}
	return (src_length);
}
