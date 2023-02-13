/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:41:41 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/18 14:41:44 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	nbr = ft_utoa(n);
	*len_nbr = ft_strlen(nbr);
	*len_prec = *len_nbr;
	if (conv->dot && conv->prec > *len_nbr)
		*len_prec = conv->prec;
	return (nbr);
}

static void	ft_printblank_width(t_conv *conv, unsigned int n, int len_prec)
{
	if (conv->width > len_prec && !conv->minus)
	{
		if (conv->zero)
		{
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

static void	ft_print_prec(int len_prec,	int len_nbr)
{
	ft_printblank('0', len_prec - len_nbr);
}

int	ft_printunbr(t_conv *conv, unsigned int n)
{
	char	*nbr;
	int		len_prec;
	int		len_nbr;

	nbr = ft_init_nbr(conv, n, &len_prec, &len_nbr);
	if (conv->width > len_prec && !conv->minus)
		ft_printblank_width(conv, n, len_prec);
	ft_print_prec(len_prec, len_nbr);
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
