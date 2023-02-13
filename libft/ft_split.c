/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:27:16 by aquincho          #+#    #+#             */
/*   Updated: 2022/05/05 12:27:18 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			res++;
		i++;
	}
	return (res);
}

static char	*ft_write_word(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	ft_free_split(char **split, int wrd_cnt)
{
	int	i;

	i = 0;
	while (i < wrd_cnt)
	{
		free(split[wrd_cnt]);
		i++;
	}
	free(split);
}

static int	ft_process_split(char **split, char *str, char c, int wrds_cnt)
{
	int	i;
	int	j;
	int	wrd_cnt;

	i = 0;
	wrd_cnt = 0;
	while (str[i] && wrd_cnt < wrds_cnt)
	{
		while (str[i] == c)
			i++;
		j = 0;
		while (!(str[i + j] == c || str[i + j] == '\0'))
			j++;
		split[wrd_cnt] = malloc((j + 1) * sizeof(char));
		if (!split[wrd_cnt])
		{
			ft_free_split(split, wrd_cnt);
			return (0);
		}
		split[wrd_cnt] = ft_write_word(split[wrd_cnt], str + i, j);
		wrd_cnt++;
		i += j;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		wrds_cnt;
	char	**res;
	char	*str;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	wrds_cnt = ft_word_count(str, c);
	res = malloc((wrds_cnt + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	if (wrds_cnt)
		if (!ft_process_split(res, str, c, wrds_cnt))
			return (NULL);
	res[wrds_cnt] = 0;
	return (res);
}
