/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:22:54 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/09/26 14:22:11 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	int		l_size;

	l_size = ft_strlen((char *)little);
	j = 0;
	i = 0;
	if (!little || l_size == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while ((little[j] == big[i + j]) && (little[j]))
			j++;
		if (little[j] == '\0' && (i + j) <= len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
