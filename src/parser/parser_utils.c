/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:50:20 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 11:25:55 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**ft_tabdup_addline(char **tab, char *line, int size)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		result[i] = ft_strdup(tab[i]);
		i++;
	}
	if (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		result[i] = ft_strdup(line);
	}
	else
		result[i] = ft_strdup(tab[i]);
	result[size] = NULL;
	return (result);
}
