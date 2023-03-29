/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:50:20 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/29 14:29:25 by aquincho         ###   ########.fr       */
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

int	ft_check_inset(char *line, char *set)
{
	int		i;
	int		j;
	bool	not_in_set;

	i = 0;
	while (line[i])
	{
		not_in_set = true;
		j = 0;
		while (set[j])
		{
			if (line[i] == set[j])
				not_in_set = false;
			j++;
		}
		if (not_in_set)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_start_pos(t_data *data, int i, int j)
{
	data->start_pos.x = i;
	data->start_pos.y = j;
	if (data->map[i][j] == 'N' || data->map[i][j] == 'S')
	{
		data->start_dir.x = 0;
		if (data->map[i][j] == 'N')
			data->start_dir.y = -1;
		else
			data->start_dir.y = 1;
	}
	else if (data->map[i][j] == 'W' || data->map[i][j] == 'E')
	{
		data->start_dir.y = 0;
		if (data->map[i][j] == 'E')
			data->start_dir.x = 1;
		else
			data->start_dir.x = -1;
	}
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
			
			while (j < (int)ft_strlen((map[i])) && map[i][j] == ' ')
			{
				if ((i > 0 
					&& !(map[i - 1][j] == ' ' || map[i - 1][j] == '1'))
					|| (i < data->height - 1
					&& !(map[i + 1][j] == ' ' || map[i + 1][j] == '1'))
					|| (map[i][j - 1] 
					&& !(map[i][j - 1] == ' ' || map[i][j - 1] == '1'))
					|| (map[i][j + 1] 
					&& !(map[i][j + 1] == ' ' || map[i][j + 1] == '1')))
					return (EXIT_FAILURE);
				j++;
			}
			if ((i == 0 || i == data->height - 1
				|| j == 0 || j == (int)ft_strlen(map[i]) - 1)
				&& !(map[i][j] == '1' || map[i][j] == ' '))
				return (EXIT_FAILURE);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				ft_start_pos(data, i, j);
				if (nb_perso < 1)
					nb_perso++;
				else
					return (EXIT_FAILURE);
			}
			if (map[i][j] == '0' && (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
			|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
				return (EXIT_FAILURE);
			if (map[i][j] == '0' && ((i > 0
				&& j > (int)ft_strlen(map[i - 1]))
				|| (i < data->height - 1 && j > (int)ft_strlen(map[i - 1]))))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	(void)data;
	return (EXIT_SUCCESS);
}
