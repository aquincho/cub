/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:23:57 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/18 11:11:52 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_color	init_color(int n)
{
	t_color	result;

	result.r = n;
	result.g = n;
	result.b = n;
	return (result);
}

inline static void	init_data_read(t_data *data)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		data->data_read[i] = 0;
		i++;
	}
}

static int	init_map(t_data *data)
{
	int	i;

	data->name = NULL;
	data->map = NULL;
	data->width = 0;
	data->height = 0;
	init_data_read(data);
	data->map_done = false;
	set_pos(&data->start_pos, 0, 0);
	set_pos(&data->start_dir, 0, 0);
	i = -1;
	while (++i < NB_TEXTURES)
		data->texture[i] = NULL;
	data->ceil = init_color(0);
	data->floor = init_color(0);
	return (EXIT_SUCCESS);
}

int	init_game(t_game *game)
{
	int	i;

	i = 0;
	game->mlx = NULL;
	game->win.ptr = NULL;
	game->img.ptr = NULL;
	game->img_minimap.ptr = NULL;
	while (i < NB_TEXTURES)
	{
		game->texture[i].ptr = NULL;
		game->texture[i].addr = NULL;
		i++;
	}
	game->mouse_x = 0;
	game->mmap_size.x = 0;
	game->mmap_size.y = 0;
	game->mmap_ratio = 1;
	game->exit_status = EXIT_SUCCESS;
	if (init_map(&game->data))
		return (display_error(sys_err, NULL));
	return (game->exit_status);
}
