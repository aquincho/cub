/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:30:53 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/03 10:30:59 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	if (tmp2 < tmp1)
	{
		while (n > 0)
		{
			n--;
			*(tmp1 + n) = *(tmp2 + n);
		}
	}
	else if (tmp1 < tmp2)
	{
		while (i < n)
		{
			*(tmp1 + i) = *(tmp2 + i);
			i++;
		}
	}
	return (dest);
}
