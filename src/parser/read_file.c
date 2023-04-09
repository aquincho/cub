/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:25:00 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/09 17:44:38 by troberts         ###   ########.fr       */
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

int	ft_read_file(t_game *game, char *arg)
{
	int		fd;

	if (ft_strlen(arg) < 4
		|| ft_strncmp((arg + ft_strlen(arg)- 4), ".cub", 4))
	{
		return (ft_display_error(rd_file_err, " Wrong map format."));
	}
	game->data.name = ft_substr(arg, 0, ft_strlen(arg) - 4);
	fd = open(arg, O_RDONLY);
	if (fd < 1)
		return (ft_display_error(rd_file_err, arg));
	if (ft_parser(fd, &game->data))
		return (EXIT_FAILURE);
	close(fd);
	return (0);
}
