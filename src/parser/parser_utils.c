/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:50:20 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/01 12:27:08 by aquincho         ###   ########.fr       */
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

int	ft_check_map(char **map, t_data *data)
{
	int	i;
	int j;
	int	nb_perso;

	nb_perso = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while ( j < (int)ft_strlen((map[i])))
		{
			
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
			{
				if ((map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S'
					|| map[i][j] == 'N') && nb_perso == 0)
					nb_perso++;
				else
					return (EXIT_FAILURE);
			}
			if ((i == 0 || i == data->height - 1)
				&& !(map[i][j] == '1' || map[i][j] == ' '))
					return (EXIT_FAILURE);
			if ((j == 0 || j == (int)ft_strlen(map[i]) - 1)
				&& map[i][j] != '1')
			{
				if ((j == 0 && map[i][j] != ' ')
					|| j == (int)ft_strlen(map[i]) - 1)
					return (EXIT_FAILURE);
			}
			if (((i > 0 && map[i - 1][j] == ' ')
				|| (i < data->height - 1 && map[i + 1][j] == ' ')
				|| (j > 0 && map[i][j - 1] == ' ')
				|| (j < (int)ft_strlen(map[i]) - 1 && map[i][j + 1] == ' '))
				&& !(map[i][j] == '1' || map[i][j] == ' '))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	(void)data;
	return (EXIT_SUCCESS);
}
