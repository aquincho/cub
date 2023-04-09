/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:17:43 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/09 17:44:38 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

inline static int	ft_check_line_data(char *tmp)
{
	if (ft_strncmp(tmp, "NO ", 3) && ft_strncmp(tmp, "SO ", 3)
		&& ft_strncmp(tmp, "WE ", 3) && ft_strncmp(tmp, "EA ", 3)
		&& ft_strncmp(tmp, "F ", 2) && ft_strncmp(tmp, "C ", 2)
		&& (ft_strncmp(tmp, "1", 1) && ft_strncmp(tmp, " ", 1)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_parse_line(t_data *data, char *tmp, int fd)
{
	if (ft_check_line_data(tmp))
		return (ft_display_error(file_err, " Wrong data"));
	if (!ft_strncmp(tmp, "NO ", 3)
		&& ft_texture(&data->texture[north], tmp, &data->data_read[north]))
		return (ft_display_error(file_err, " Cannot read north image file"));
	if (!ft_strncmp(tmp, "SO ", 3)
		&& ft_texture(&data->texture[south], tmp, &data->data_read[south]))
		return (ft_display_error(file_err, " Cannot read south image file"));
	if (!ft_strncmp(tmp, "WE ", 3)
		&& ft_texture(&data->texture[west], tmp, &data->data_read[west]))
		return (ft_display_error(file_err, " Cannot read west image file"));
	if (!ft_strncmp(tmp, "EA ", 3)
		&& ft_texture(&data->texture[east], tmp, &data->data_read[east]))
		return (ft_display_error(file_err, " Cannot read east image file"));
	if (!ft_strncmp(tmp, "C ", 2)
		&& ft_color(&data->ceil, tmp, &data->data_read[ceil_c]))
		return (ft_display_error(file_err, " Cannot read ceil color"));
	if (!ft_strncmp(tmp, "F ", 2)
		&& ft_color(&data->floor, tmp, &data->data_read[floor_c]))
		return (ft_display_error(file_err, " Cannot read floor color"));
	if (((!ft_strncmp(tmp, "1", 1) || !ft_strncmp(tmp, " ", 1))
			&& ft_map(data, fd, tmp)))
		return (ft_display_error(file_err, " Cannot read map"));
	return (EXIT_SUCCESS);
}

inline static void	ft_empty_lines(char **tmp, int fd)
{
	while (*tmp && !ft_strncmp(*tmp, "\n", 1))
	{
		free (*tmp);
		*tmp = get_next_line(fd);
	}
}

inline static void	ft_map_done(t_data *data, int fd, char **tmp)
{
	if (data->map_done)
		*tmp = NULL;
	else
	{
		free (*tmp);
		*tmp = get_next_line(fd);
	}
}

int	ft_parser(int fd, t_data *data)
{
	char	*tmp;
	int		nb_data;

	nb_data = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		ft_empty_lines(&tmp, fd);
		if (tmp && !ft_parse_line(data, tmp, fd))
			nb_data++;
		else if (tmp)
		{
			if (!data->map_done)
				free (tmp);
			else
				tmp = NULL;
			return (EXIT_FAILURE);
		}
		ft_map_done(data, fd, &tmp);
	}
	if (nb_data != 7)
		return (ft_display_error(file_err, " Missing data"));
	return (EXIT_SUCCESS);
}
