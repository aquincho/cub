/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:17:43 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 11:51:56 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_read_file(int fd, t_map *map)
{
	char	*tmp;

	tmp = get_next_line(fd);
	if (!ft_strncmp(tmp, "NO", 2));
		map->n_wall = ft_strdup(tmp);
	else if (!ft_strncmp(tmp, "SO", 2))
		map->s_wall = ft_strdup(tmp);
	else if (!ft_strncmp(tmp, "WE", 2))
		map->w_wall = ft_strdup(tmp);
	else if (!ft_strncmp(tmp, "EA", 2))
		map->e_wall = ft_strdup(tmp);
	else if (!ft_strncmp(tmp, "C", 1))
		map->ceil = ft_color(tmp);
	else if (!ft_strncmp(tmp, "F", 1))
		map->floor = ft_color(tmp);
	else if (!ft_strncmp(tmp, "1", 1))
		map->map = ft_read_map(tmp, fd);
}

t_map	*ft_read_mapfile(char *arg)
{
	t_map	*result;
	int		fd;

	if (ft_strlen(arg) < 4
		|| ft_strncmp((arg + ft_strlen(arg)- 4), ".cub", 4))
		ft_error_exit(filetype_err, "Wrong map format.");
	result->name = ft_substr(arg, 0, ft_strlen(arg) - 4);
	fd = open(arg, O_RDONLY);
	if (fd < 1)
		ft_error_exit(sys_err, "Cannot open file");
	ft_read_file(fd, result);
	close(fd);
	return (result);
}