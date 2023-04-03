/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:17:43 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/03 09:09:39 by aquincho         ###   ########.fr       */
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

static int	ft_parse_line(t_data *data, char *tmp, int *used, int fd)
{
	if (ft_check_line_data(tmp))
		return (ft_error(file_err, " Wrong data"));
	if (!ft_strncmp(tmp, "NO ", 3)
		&& ft_texture(&data->texture[north], tmp, &used[north]))
		return (ft_error(file_err, " Cannot read north image file"));
	if (!ft_strncmp(tmp, "SO ", 3)
		&& ft_texture(&data->texture[south], tmp, &used[south]))
		return (ft_error(file_err, " Cannot read south image file"));
	if (!ft_strncmp(tmp, "WE ", 3)
		&& ft_texture(&data->texture[west], tmp, &used[west]))
		return (ft_error(file_err, " Cannot read west image file"));
	if (!ft_strncmp(tmp, "EA ", 3)
		&& ft_texture(&data->texture[east], tmp, &used[east]))
		return (ft_error(file_err, " Cannot read east image file"));
	if (!ft_strncmp(tmp, "C ", 2)
		&& ft_color(&data->ceil, tmp, &used[ceil_c]))
		return (ft_error(file_err, " Cannot read ceil color"));
	if (!ft_strncmp(tmp, "F ", 2)
		&& ft_color(&data->ceil, tmp, &used[floor_c]))
		return (ft_error(file_err, " Cannot read floor color"));
	if (((!ft_strncmp(tmp, "1", 1) || !ft_strncmp(tmp, " ", 1))
			&& ft_map(data, fd, &tmp)))
		return (ft_error(file_err, " Cannot read map"));
	return (EXIT_SUCCESS);
}

inline static void	ft_init_used(int *used, int *nb_data)
{
	int	i;

	*nb_data = 0;
	i = 0;
	while (i < 7)
	{
		used[i] = 0;
		i++;
	}
}

inline static void	ft_empty_lines(char **tmp, int fd)
{
	while (*tmp && !ft_strncmp(*tmp, "\n", 1))
	{
		free (*tmp);
		*tmp = get_next_line(fd);
	}
}

int	ft_parser(int fd, t_data *data)
{
	char	*tmp;
	int		nb_data;
	int		used[7];

	ft_init_used(used, &nb_data);
	tmp = get_next_line(fd);
	while (tmp)
	{
		ft_empty_lines(&tmp, fd);
		if (tmp && !ft_parse_line(data, tmp, used, fd))
			nb_data++;
		else if (tmp)
		{
			free (tmp);
			return (EXIT_FAILURE);
		}
		if (tmp)
			free(tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	if (nb_data != 7)
		return (ft_error(file_err, " Missing data"));
	return (EXIT_SUCCESS);
}
