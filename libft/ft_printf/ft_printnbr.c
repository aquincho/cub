/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:40:04 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/16 12:40:07 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_val_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static char	*ft_init_nbr(t_conv *conv, int n, int *len_prec, int *len_nbr)
{
	char	*nbr;

	if (conv->dot)
		conv->zero = 0;
	if (n < 0)
	{
		conv->plus = 0;
		conv->space = 0;
	}
	nbr = ft_utoa(ft_val_abs(n));
	*len_nbr = ft_strlen(nbr);
	*len_prec = *len_nbr;
	if (conv->dot && conv->prec > *len_nbr)
		*len_prec = conv->prec;
	if ((conv->space || conv->plus) || n < 0)
		*len_prec += 1;
	return (nbr);
}

static void	ft_printblank_width(t_conv *conv, int n, int len_prec)
{
	if (conv->width > len_prec && !conv->minus)
	{
		if (conv->zero)
		{
			if (n < 0)
				write(1, "-", 1);
			ft_printblank('0', conv->width - len_prec);
		}
		else
			ft_printblank(' ', conv->width - len_prec
				+ (n == 0 && conv->dot && !conv->prec));
	}
	if (conv->width > len_prec && conv->minus)
	{
		if (conv->zero)
			ft_printblank('0', conv->width - len_prec);
		else
			ft_printblank(' ', conv->width - len_prec);
	}
}

static void	ft_print_prec(t_conv *conv, int n, int len_prec, int len_nbr)
{
	if (conv->space && n >= 0)
		write(1, " ", 1);
	if (conv->plus && n >= 0)
		write(1, "+", 1);
	if (n < 0 && !(conv->width > len_prec && !conv->minus && conv->zero))
		write(1, "-", 1);
	ft_printblank('0', len_prec - len_nbr - (conv->space || conv->plus)
		- (n < 0));
}

int	ft_printnbr(t_conv *conv, int n)
{
	char	*nbr;
	int		len_prec;
	int		len_nbr;

	nbr = ft_init_nbr(conv, n, &len_prec, &len_nbr);
	if (conv->width > len_prec && !conv->minus)
		ft_printblank_width(conv, n, len_prec);
	ft_print_prec(conv, n, len_prec, len_nbr);
	if (!(conv->dot && !conv->prec && n == 0))
		write(1, nbr, len_nbr);
	else
	{
		if (n == 0 && conv->dot && !conv->prec && conv->width == 1)
			write(1, " ", 1);
		len_prec--;
	}
	if (conv->width > len_prec && conv->minus)
		ft_printblank_width(conv, n, len_prec);
	free (nbr);
	if (conv->width > len_prec)
		return (conv->width);
	return (len_prec);
}
