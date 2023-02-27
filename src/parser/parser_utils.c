/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:50:20 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/27 12:06:43 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_file(char *path)
{
	int	tmp_fd;

	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd > 0)
		close (tmp_fd);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	**ft_tabdup_addline(char **tab, char *line, int size)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (size + 1));
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