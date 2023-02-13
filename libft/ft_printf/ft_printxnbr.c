/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printxnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:40:04 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/16 12:40:07 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_init_nbr(t_conv *conv, int n, int *len_prec, int *len_nbr)
{
	if (conv->dot)
		conv->zero = 0;
	if (n == 0)
		conv->hash = 0;
	*len_nbr = ft_nbrlen(n, 16);
	*len_prec = *len_nbr;
	if (conv->dot && conv->prec > *len_nbr)
		*len_prec = conv->prec;
}

static int	ft_printblank_width(t_conv *conv, int n, int len_prec, char x)
{
	if (conv->width > len_prec && !conv->minus)
	{
		if (conv->zero)
		{
			if (conv->hash && n != 0)
			{
				write(1, "0", 1);
				write(1, &x, 1);
				len_prec += 2;
			}
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
	return (len_prec);
}

static int	ft_print_prec(t_conv *conv, int len_prec, int len_nbr, char x)
{
	if (conv->hash && !(conv->width > len_prec && !conv->minus && conv->zero))
	{
		write(1, "0", 1);
		write(1, &x, 1);
		len_prec += 2;
	}
	ft_printblank('0', len_prec - len_nbr - 2 * conv->hash);
	return (len_prec);
}

static void	ft_puthex(unsigned int n, char x)
{
	if (n >= 16)
	{
		ft_puthex(n / 16, x);
		ft_puthex(n % 16, x);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
		{
			if (x == 'x')
				ft_putchar_fd((n - 10 + 'a'), 1);
			if (x == 'X')
				ft_putchar_fd((n - 10 + 'A'), 1);
		}
	}
}

int	ft_printxnbr(t_conv *conv, int n, char x)
{
	int	len_nbr;
	int	len_prec;

	ft_init_nbr(conv, n, &len_prec, &len_nbr);
	if (conv->width > len_prec && !conv->minus)
		len_prec = ft_printblank_width(conv, n, len_prec, x);
	len_prec = ft_print_prec(conv, len_prec, len_nbr, x);
	if (!(conv->dot && !conv->prec && n == 0))
		ft_puthex(n, x);
	else
	{
		if (n == 0 && conv->dot && !conv->prec && conv->width == 1)
			write(1, " ", 1);
		len_prec--;
	}
	if (conv->width > len_prec && conv->minus)
		len_prec = ft_printblank_width(conv, n, len_prec, x);
	if (conv->width > len_prec)
		return (conv->width);
	return (len_prec);
}
