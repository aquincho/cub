/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:39:34 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/16 12:39:36 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(t_conv *conv, int c)
{
	int	len;

	len = 1;
	if (conv->width > 1)
		len = conv->width;
	if (!conv->minus && len > 1)
		ft_printblank(' ', len - 1);
	write(1, &c, 1);
	if (conv->minus && len > 1)
		ft_printblank(' ', len - 1);
	return (len);
}

int	ft_printstr(t_conv *conv, char *s)
{
	int	len;

	if ((!s && !conv->dot) || (!s && conv->dot && conv->prec >= 6))
		len = 6;
	else if (!s && conv->dot && conv->prec < 6)
		len = 0;
	else if (conv->dot && conv->prec < (int)ft_strlen(s))
		len = conv->prec;
	else
		len = ft_strlen(s);
	if (!conv->minus && conv->width > len)
		ft_printblank(' ', conv->width - len);
	if ((!s && !conv->dot) || (!s && conv->dot && conv->prec > 5))
		write(1, "(null)", 6);
	else
		write(1, s, len);
	if (conv->minus && conv->width > len)
		ft_printblank(' ', conv->width - len);
	if (conv->width > len)
		return (conv->width);
	return (len);
}
