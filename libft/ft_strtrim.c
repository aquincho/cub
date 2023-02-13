/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:39:35 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/05 15:40:00 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*rtrim(const char *s, size_t len, const char *set)
{
	char	*dst;
	size_t	i;

	while (isset(*(s + len - 1), set))
		len --;
	i = 0;
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		*(dst + i) = *(s + i);
		i++;
	}
	*(dst + i) = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	i;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (isset(*(s1 + i), set))
		i++;
	if (i == len)
	{
		dst = malloc(sizeof(char));
		*dst = '\0';
	}
	else
		dst = rtrim(s1 + i, len - i, set);
	if (!dst)
		return (NULL);
	return (dst);
}
