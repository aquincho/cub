/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:40:04 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/16 12:40:07 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_lenptr(uintptr_t p)
{
	int	len;

	len = 0;
	while (p != 0)
	{
		len++;
		p = p / 16;
	}
	return (len);
}

static void	ft_putptr(uintptr_t p)
{
	if (p >= 16)
	{
		ft_putptr(p / 16);
		ft_putptr(p % 16);
	}
	else
	{
		if (p <= 9)
			ft_putchar_fd((p + '0'), 1);
		else
			ft_putchar_fd((p - 10 + 'a'), 1);
	}
}

int	ft_printptr(t_conv *conv, unsigned long int p)
{
	int	len;

	if (!p)
		len = 5;
	else
		len = ft_lenptr(p) + 2;
	if (!conv->minus && conv->width > len)
		ft_printblank(' ', conv->width - len);
	if (!p)
		write(1, "(nil)", 5);
	else
	{
		write(1, "0x", 2);
		ft_putptr(p);
	}
	if (conv->minus && conv->width > len)
		ft_printblank(' ', conv->width - len);
	if (conv->width > len)
		return (conv->width);
	return (len);
}
