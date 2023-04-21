/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:34:58 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/12 14:28:28 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	map_line(t_data *data, char *line, char ***tmp)
{
	if (check_inset(line, MAP_CHAR))
		return (EXIT_FAILURE);
	data->height++;
	if ((int)ft_strlen(line) > data->width)
		data->width = ft_strlen(line) - 1;
	*tmp = tabdup_addline(data->map, line, data->height);
	if (!(**tmp))
		return (EXIT_FAILURE);
	e_tab(data->map);
	data->map = tabdup_addline(*tmp, NULL, data->height);
	if (!data->map)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	map(t_data *data, int fd, char *line)
{
	char	**tmp;

	tmp = NULL;
	while (line && (!ft_strncmp(line, "1", 1) || !ft_strncmp(line, " ", 1)))
	{
		if (map_line(data, line, &tmp))
		{
			free(line);
			line = NULL;
			return (EXIT_FAILURE);
		}
		free_tab(tmp);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free (line);
	data->map_done = true;
	if (check_map(data->map, data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
