/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:50:43 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/09 17:44:38 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_space(char **map, int i, int *j)
{
	if (map[i][*j - 1] != '1')
		return (EXIT_FAILURE);
	while (map[i][*j] == ' ')
		(*j)++;
	if (map[i][*j] != '1')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_wall(char **map, t_data *data, int i)
{
	int	j;
	int	k;

	j = 0;
	while (map[i][j] == ' ')
		j++;
	k = ft_strlen(map[i]) - 1;
	while (map[i][k] == ' ')
		k--;
	if (map[i][j] != '1' || map [i][k] != '1')
		return (EXIT_FAILURE);
	while (j < k)
	{
		if ((i == 0 || i == data->height - 1)
			&& !(map[i][j] == '1' || map[i][j] == ' '))
			return (EXIT_FAILURE);
		else if ((i > 0 && i < data->height))
		{
			if (map[i][j] == ' ' && check_space(map, i, &j))
				return (EXIT_FAILURE);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

static int	check_zero(char **map, t_data *data, int i, int j)
{
	if (map[i][j] == '0' && (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
		|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
		return (EXIT_FAILURE);
	if (map[i][j] == '0' && ((i > 0
		&& j > (int)ft_strlen(map[i - 1]))
		|| (i < data->height - 1 && j > (int)ft_strlen(map[i - 1]))))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_line(char **map, t_data *data, int i, int *nb_perso)
{
	int	j;

	if (check_wall(map, data, i))
		return (display_error(file_err, "Wall incomplete"));
	j = 0;
	while (j < (int)ft_strlen((map[i])))
	{
		if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
			|| map[i][j] == 'E')
		{
			start_pos(data, i, j);
			if (*nb_perso < 1)
				(*nb_perso)++;
			else
				return (display_error(file_err, "Too many start positions"));
		}
		if (check_zero(map, data, i, j))
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(char **map, t_data *data)
{
	int	i;
	int	nb_perso;

	nb_perso = 0;
	i = 0;
	while (map[i])
	{
		if (check_line(map, data, i, &nb_perso))
			return (EXIT_FAILURE);
		i++;
	}
	if (nb_perso != 1)
		return (display_error(file_err, "missing start position"));
	return (EXIT_SUCCESS);
}
