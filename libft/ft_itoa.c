/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:55:59 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/05 12:56:45 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_nbr(long n)
{
	int	res;

	res = 1;
	if (n < 0)
	{
		n = -n;
		res++;
	}
	while (n > 9)
	{
		n /= 10;
		res++;
	}
	return (res);
}

static void	ft_putnbr(long n, char *res, int *i)
{
	if (n > 9)
	{
		ft_putnbr(n / 10, res, i);
		ft_putnbr(n % 10, res, i);
	}
	else
		res[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*res;
	long	ln;
	int		len_nbr;
	int		i;

	ln = n;
	len_nbr = ft_len_nbr(ln);
	res = malloc((len_nbr + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (ln < 0)
	{
		res[i] = '-';
		ln = -ln;
		i++;
	}
	ft_putnbr(ln, res, &i);
	res[i] = '\0';
	return (res);
}

char	*ft_utoa(unsigned int n)
{
	char	*res;
	long	ln;
	int		len_nbr;
	int		i;

	ln = n;
	len_nbr = ft_len_nbr(ln);
	res = malloc((len_nbr + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (ln < 0)
	{
		res[i] = '-';
		ln = -ln;
		i++;
	}
	ft_putnbr(ln, res, &i);
	res[i] = '\0';
	return (res);
}
