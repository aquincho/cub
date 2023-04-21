/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:50:20 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/12 13:12:41 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**tabdup_addline(char **tab, char *line, int size)
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
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		result[i] = ft_strdup(line);
	}
	else
		result[i] = ft_strdup(tab[i]);
	result[size] = NULL;
	return (result);
}

int	texture(char **texture, char *line, int *used)
{
	char	**tmp;

	if (*used > 0)
		return (display_error(file_err, " same texture twice"));
	(*used) += 1;
	tmp = ft_split(line, ' ');
	if (tmp[1])
		*texture = ft_strdup(tmp[1]);
	texture[0][ft_strlen(*texture) - 1] = '\0';
	free_tab(tmp);
	if (check_file(*texture))
		return (display_error(file_err, " Cannot read image file"));
	return (EXIT_SUCCESS);
}

static int	set_color(t_color *color, char **tmp)
{
	color->r = ft_atoi(tmp[0]);
	color->g = ft_atoi(tmp[1]);
	color->b = ft_atoi(tmp[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	color(t_color *color, char *line, int *used)
{
	char	**tmp;
	int		i;

	if (*used > 0)
		return (display_error(file_err, " same color twice"));
	(*used)++;
	while (!ft_isdigit(*line))
		line++;
	if (!*line)
		return (display_error(file_err, " Cannot read color"));
	if (ft_strchr(line, ','))
		tmp = ft_split(line, ',');
	else
		return (display_error(file_err, " Cannot read color"));
	i = 0;
	while (tmp[i])
		i++;
	if (i != 3 || set_color(color, tmp))
	{
		free_tab(tmp);
		return (display_error(file_err, " Cannot read color"));
	}
	free_tab(tmp);
	return (EXIT_SUCCESS);
}

void	start_pos(t_data *data, int i, int j)
{
	data->start_pos.x = j;
	data->start_pos.y = i;
	if (data->map[i][j] == 'W' || data->map[i][j] == 'E')
	{
		data->start_dir.y = 0;
		if (data->map[i][j] == 'W')
			data->start_dir.x = -1;
		else
			data->start_dir.x = 1;
	}
	else if (data->map[i][j] == 'N' || data->map[i][j] == 'S')
	{
		data->start_dir.x = 0;
		if (data->map[i][j] == 'N')
			data->start_dir.y = -1;
		else
			data->start_dir.y = 1;
	}
}
