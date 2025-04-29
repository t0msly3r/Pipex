/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:25:59 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/10/02 17:15:41 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		size;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	size = s1_len + s2_len + 1;
	str = malloc(size);
	if (!str)
		return (NULL);
	ft_memmove(str, (char *)s1, s1_len);
	ft_memmove(str + s1_len, (char *)s2, s2_len);
	str[size - 1] = '\0';
	return (str);
}
