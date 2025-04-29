/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:19:06 by tfiz-ben          #+#    #+#             */
/*   Updated: 2024/10/05 12:29:19 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countlen(char *s, char c, int start)
{
	int	i;

	i = 0;
	while (s[i + start] && s[i + start] != c)
		i++;
	return (i);
}

void	free_ar(char **result, int num)
{
	while (num >= 0)
		free(result[num--]);
	free(result);
}

char	**create_subs(char *s, char c, char **result, int num)
{
	int	pos;
	int	len;

	pos = 0;
	len = 0;
	while (s[pos])
	{
		while (s[pos] == c)
			pos++;
		if (s[pos])
		{
			len = countlen((char *)s, c, pos);
			result[num] = ft_substr(s, pos, len);
			if (!result[num])
			{
				free_ar(result, num);
				return (NULL);
			}
			num++;
			pos += len;
		}
	}
	result[num] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		num;
	char	**result;
	int		deln;
	int		i;

	num = 0;
	deln = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			deln++;
		i++;
	}
	result = malloc((deln + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (create_subs((char *)s, c, result, num));
}
