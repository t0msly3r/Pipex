/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:22:30 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/09/25 11:01:30 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		pos;
	int		i;
	int		find;
	char	cc;

	cc = (char)c;
	i = 0;
	find = 0;
	while (s[i])
	{
		if (s[i] == cc)
		{
			pos = i;
			find = 1;
		}
		i++;
	}
	if (s[i] == cc)
		return ((char *)s + i);
	else if (find == 1)
		return ((char *)s + pos);
	else
		return (NULL);
}
