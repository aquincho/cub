/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:45:41 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/18 11:10:07 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (EXIT_FAILURE);
	set_pos(&game->win.size, (double)WIN_WIDTH, (double)WIN_HEIGHT);
	game->win.ptr = mlx_new_window(game->mlx, game->win.size.x,
			game->win.size.y, "CUB3D");
	if (!game->win.ptr)
		return (EXIT_FAILURE);
	game->img.ptr = mlx_new_image(game->mlx, game->win.size.x,
			game->win.size.y);
	if (!game->img.ptr)
		return (EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	size_mmap(game);
	game->img_minimap.ptr = mlx_new_image(game->mlx, game->mmap_size.x,
			game->mmap_size.y);
	if (!game->img_minimap.ptr)
		return (EXIT_FAILURE);
	game->img_minimap.addr = mlx_get_data_addr(game->img_minimap.ptr,
			&game->img_minimap.bpp, &game->img_minimap.line_len,
			&game->img_minimap.endian);
	return (0);
}

static int	get_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		game->texture[i].width = TEX_SIZE;
		game->texture[i].height = TEX_SIZE;
		game->texture[i].ptr = mlx_xpm_file_to_image(game->mlx,
				game->data.texture[i], &game->texture[i].width,
				&game->texture[i].height);
		if (!game->texture[i].ptr)
			return (EXIT_FAILURE);
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].ptr,
				&game->texture[i].bpp, &game->texture[i].line_len,
				&game->texture[i].endian);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_draw(t_game *game)
{
	set_pos(&game->cam.pos, game->data.start_pos.x, game->data.start_pos.y);
	set_pos(&game->cam.dir, game->data.start_dir.x, game->data.start_dir.y);
	game->data.map[(int)game->data.start_pos.y][(int)game->data.start_pos.x]
		= '0';
	if (game->data.start_dir.y == 1)
		set_pos(&game->cam.plane, -0.66, 0);
	else if (game->data.start_dir.y == -1)
		set_pos(&game->cam.plane, 0.66, 0);
	else if (game->data.start_dir.x == 1)
		set_pos(&game->cam.plane, 0, 0.66);
	else if (game->data.start_dir.x == -1)
		set_pos(&game->cam.plane, 0, -0.66);
	game->cam.move_speed = MOVE_SPEED;
	game->cam.rot_speed = ROT_SPEED;
	game->show_minimap = false;
	if (get_texture(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
