/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 09:46:53 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/13 09:46:57 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_readformat(char *format, t_conv *conv, va_list args)
{
	int	i;
	int	len_total;

	i = 0;
	len_total = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i = ft_process_conv(conv, args, (char *)format, i + 1);
			if (!i)
				return (0);
			len_total += conv->len_print;
		}
		else
		{
			i += write(1, &format[i], 1);
			len_total++;
		}
	}
	return (len_total);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_conv	*conv;
	int		len_total;

	len_total = 0;
	conv = (t_conv *)malloc(sizeof(t_conv));
	if (!conv)
		return (-1);
	va_start(args, format);
	len_total = ft_readformat((char *)format, conv, args);
	va_end(args);
	free(conv);
	return (len_total);
}
