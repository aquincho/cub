/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:43:35 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/04 11:43:39 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = (char *)s;
	if (c < 0)
		return (NULL);
	if (c > 255)
		return (NULL);
	while (s[len])
		len++;
	tmp = (char *)s;
	while (len >= 0)
	{
		if (*(tmp + len) == c)
			return (tmp + len);
		len--;
	}
	return (NULL);
}
