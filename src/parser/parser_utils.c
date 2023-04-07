/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:50:20 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/07 12:16:06 by aquincho         ###   ########.fr       */
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

int	ft_texture(char **texture, char *line, int *used)
{
	char	**tmp;

	if (*used > 0)
		return (ft_error(file_err, " same texture twice"));
	(*used) += 1;
	tmp = ft_split(line, ' ');
	if (tmp[1])
		*texture = ft_strdup(tmp[1]);
	texture[0][ft_strlen(*texture) - 1] = '\0';
	ft_free_tab(tmp);
	if (ft_check_file(*texture))
		return (ft_error(file_err, " Cannot read image file"));
	return (EXIT_SUCCESS);
}

static int	ft_set_color(t_color *color, char **tmp)
{
	color->r = ft_atoi(tmp[0]);
	color->g = ft_atoi(tmp[1]);
	color->b = ft_atoi(tmp[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_color(t_color *color, char *line, int *used)
{
	char	**tmp;
	int		i;

	if (*used > 0)
		return (ft_error(file_err, " same color twice"));
	(*used)++;
	while (!ft_isdigit(*line))
		line++;
	if (!*line)
		return (ft_error(file_err, " Cannot read color"));
	if (ft_strchr(line, ','))
		tmp = ft_split(line, ',');
	else
		return (ft_error(file_err, " Cannot read color"));
	i = 0;
	while (tmp[i])
		i++;
	if (i != 3 || ft_set_color(color, tmp))
	{
		ft_free_tab(tmp);
		return (ft_error(file_err, " Cannot read color"));
	}
	ft_free_tab(tmp);
	return (EXIT_SUCCESS);
}

void	ft_start_pos(t_data *data, int i, int j)
{
	data->start_pos.x = i;
	data->start_pos.y = j;
	if (data->map[i][j] == 'N' || data->map[i][j] == 'S')
	{
		data->start_dir.y = 0;
		if (data->map[i][j] == 'N')
			data->start_dir.x = -1;
		else
			data->start_dir.x = 1;
	}
	else if (data->map[i][j] == 'W' || data->map[i][j] == 'E')
	{
		data->start_dir.x = 0;
		if (data->map[i][j] == 'E')
			data->start_dir.y = 1;
		else
			data->start_dir.y = -1;
	}
}
