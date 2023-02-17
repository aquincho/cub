/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:17:43 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/17 10:12:25 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_map(t_map *map, int fd, char *line)
{
	char	**tmp;

	tmp = malloc(sizeof(char *));
	*tmp = ft_strdup(line);
	map->width = ft_strlen(line);
	while (line && (!ft_strncmp(line, "1", 1) || !ft_strncmp(line, " ", 1)))
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
		
	}
	return (0);
}

static int	ft_texture(char *texture, char *line)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	if (tmp[1])
		texture = ft_strdup(tmp[1]);
	if (ft_check_file(texture))
		return (1);
	return (0);
}

static int	ft_color(t_color *color, char *line)
{
	char	**tmp;
	int		i;

	while (!ft_isdigit(*line)) 
		line++;
	tmp = ft_split(line, ',');
	i = 0;
	while(tmp[i])
		i++;
	if (i != 3)
	{
		i = 0;
		while (tmp[i])
			free(tmp[i]);
		free(tmp);
		return (1);
	}
	color->r = ft_atoi(tmp[0]);
	color->g = ft_atoi(tmp[1]);
	color->b = ft_atoi(tmp[2]);
	return (0);
}

static int	ft_parser(int fd, t_map *map)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		if (!ft_strncmp(tmp, "NO", 2) && ft_texture(map->n_wall, tmp))
			return (ft_error(file_err, " Cannot read north image file"));
		else if (!ft_strncmp(tmp, "SO", 2) && ft_texture(map->s_wall, tmp))
			return (ft_error(file_err, " Cannot read south image file"));
		else if (!ft_strncmp(tmp, "WE", 2) && ft_texture(map->w_wall, tmp))
			return (ft_error(file_err, " Cannot read south image file"));
		else if (!ft_strncmp(tmp, "EA", 2) && ft_texture(map->e_wall, tmp))
			return (ft_error(file_err, " Cannot read south image file"));
		else if (!ft_strncmp(tmp, "C", 1) && ft_color(&map->ceil, tmp))
			return (ft_error(file_err, " Cannot read color"));
		else if (!ft_strncmp(tmp, "F", 1) && ft_color(&map->floor, tmp))
			return (ft_error(file_err, " Cannot read color"));
		else if ((!ft_strncmp(tmp, "1", 1) || !ft_strncmp(tmp, " ", 1))
			&& ft_map(map, fd, tmp))
			return (ft_error(file_err, " Cannot parse map"));
		else if (ft_strncmp(tmp, "\n", 1))
			return (ft_error(file_err, " Invalid line."));
		tmp = get_next_line(fd);
	}
	return (0);
}

int	ft_read_file(t_game *game, char *arg)
{
	int		fd;

	if (ft_strlen(arg) < 4
		|| ft_strncmp((arg + ft_strlen(arg)- 4), ".cub", 4))
	{
		ft_error(file_err, " Wrong map format.");
		return (ft_error(file_err, " Wrong map format."));
	}
	game->map->name = ft_substr(arg, 0, ft_strlen(arg) - 4);
	fd = open(arg, O_RDONLY);
	if (fd < 1)
		return (ft_error(file_err, arg));
	if (ft_parser(fd, game->map))
	{
		close (fd);
		ft_error_exit(file_err, NULL, game);
	}
	close(fd);
	return (0);
}