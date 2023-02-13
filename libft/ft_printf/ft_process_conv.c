/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:44:49 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/16 09:44:52 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_init_conv(t_conv *conv)
{
	conv->minus = 0;
	conv->zero = 0;
	conv->hash = 0;
	conv->space = 0;
	conv->plus = 0;
	conv->dot = 0;
	conv->prec = 0;
	conv->width = 0;
	conv->len_print = 0;
}

static int	ft_isconv(char c)
{
	int		i;
	char	*conv;

	conv = "cspdiuxX%";
	i = 0;
	while (conv[i])
	{
		if (conv[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_process_width(t_conv *conv, char *format, int i)
{
	if (format[i] == '.')
	{
		conv->dot = 1;
		if (format[i + 1] >= '0' && format[i + 1] <= '9')
		{
			conv->prec = ft_atoi(format + i + 1);
			i += ft_nbrlen(conv->prec, 10);
		}
	}
	else if (format[i] > '0' && format[i] <= '9' && format[i - 1] != '.')
	{
		conv->width = ft_atoi(format + i);
		i += ft_nbrlen(conv->width, 10) - 1;
	}
	else
		return (0);
	return (i);
}

int	ft_process_flags(t_conv *conv, char *format, int i)
{
	ft_init_conv(conv);
	while (!ft_isconv(format[i]) && format[i])
	{
		if (format[i] == '-')
			conv->minus = 1;
		else if (format[i] == '0' && format[i - 1] != '.')
			conv->zero = 1;
		else if (format[i] == '#')
			conv->hash = 1;
		else if (format[i] == ' ')
			conv->space = 1;
		else if (format[i] == '+')
			conv->plus = 1;
		else
			i = ft_process_width(conv, format, i);
		i++;
	}
	if (format[i] == '\0')
		return (0);
	return (i);
}

int	ft_process_conv(t_conv *conv, va_list args, char *format, int i)
{
	i = ft_process_flags(conv, format, i);
	if (!i)
		return (0);
	if (format[i] == 'c')
		conv->len_print = ft_printchar(conv, va_arg(args, int));
	if (format[i] == 's')
		conv->len_print = ft_printstr(conv, va_arg(args, char *));
	if (format[i] == 'd' || format[i] == 'i')
		conv->len_print = ft_printnbr(conv, va_arg(args, int));
	if (format[i] == 'u')
		conv->len_print = ft_printunbr(conv, va_arg(args, int));
	if (format[i] == 'x' || format[i] == 'X')
		conv->len_print = ft_printxnbr(conv, va_arg(args, int), format[i]);
	if (format[i] == 'p')
		conv->len_print = ft_printptr(conv, va_arg(args, unsigned long int));
	if (format[i] == '%')
		conv->len_print = write(1, "%", 1);
	return (i + 1);
}
