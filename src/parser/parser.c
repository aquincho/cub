/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:17:43 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/17 19:05:37 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

inline static int	check_line_data(char *tmp)
{
	if (ft_strncmp(tmp, "NO ", 3) && ft_strncmp(tmp, "SO ", 3)
		&& ft_strncmp(tmp, "WE ", 3) && ft_strncmp(tmp, "EA ", 3)
		&& ft_strncmp(tmp, "F ", 2) && ft_strncmp(tmp, "C ", 2)
		&& (ft_strncmp(tmp, "1", 1) && ft_strncmp(tmp, " ", 1)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_line(t_data *data, char *tmp, int fd)
{
	if (check_line_data(tmp))
		return (display_error(file_err, " Wrong data"));
	if (!ft_strncmp(tmp, "NO ", 3)
		&& texture(&data->texture[north], tmp, &data->data_read[north]))
		return (display_error(file_err, " Cannot read north image file"));
	if (!ft_strncmp(tmp, "SO ", 3)
		&& ft_texture(&data->texture[south], tmp, &data->data_read[south]))
		return (display_error(file_err, " Cannot read south image file"));
	if (!ft_strncmp(tmp, "WE ", 3)
		&& texture(&data->texture[west], tmp, &data->data_read[west]))
		return (display_error(file_err, " Cannot read west image file"));
	if (!ft_strncmp(tmp, "EA ", 3)
		&& texture(&data->texture[east], tmp, &data->data_read[east]))
		return (display_error(file_err, " Cannot read east image file"));
	if (!ft_strncmp(tmp, "C ", 2)
		&& color(&data->ceil, tmp, &data->data_read[ceil_c]))
		return (display_error(file_err, " Cannot read ceil color"));
	if (!ft_strncmp(tmp, "F ", 2)
		&& color(&data->floor, tmp, &data->data_read[floor_c]))
		return (display_error(file_err, " Cannot read floor color"));
	if (((!ft_strncmp(tmp, "1", 1) || !ft_strncmp(tmp, " ", 1))
			&& map(data, fd, tmp)))
		return (display_error(file_err, " Cannot read map"));
	return (EXIT_SUCCESS);
}

inline static void	empty_lines(char **tmp, int fd)
{
	while (*tmp && !ft_strncmp(*tmp, "\n", 1))
	{
		free (*tmp);
		*tmp = get_next_line(fd);
	}
}

inline static void	map_done(t_data *data, int fd, char **tmp)
{
	if (data->map_done)
		*tmp = NULL;
	else
	{
		free (*tmp);
		*tmp = get_next_line(fd);
	}
}

int	parser(int fd, t_data *data)
{
	char	*tmp;
	int		nb_data;

	nb_data = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		empty_lines(&tmp, fd);
		if (tmp && !parse_line(data, tmp, fd))
			nb_data++;
		else
		{
			free (tmp);
			return (EXIT_FAILURE);
		}
		map_done(data, fd, &tmp);
	}
	if (nb_data != 7)
		return (display_error(file_err, " Missing data"));
	return (EXIT_SUCCESS);
}
