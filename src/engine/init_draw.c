/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:45:41 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/09 17:25:21 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (EXIT_FAILURE);
	ft_set_pos(&game->win.size, (double)WIN_WIDTH, (double)WIN_HEIGHT);
	game->win.ptr = mlx_new_window(game->mlx, game->win.size.x,
			game->win.size.y, "CUB3D");
	if (!game->win.ptr)
		return (EXIT_FAILURE);
	game->img.ptr = mlx_new_image(game->mlx, game->win.size.x,
			game->win.size.y);
	if (!game->img.ptr)
		return (EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_len, &game->img.line_len);
	return (0);
}

static int	ft_get_texture(t_game *game)
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

int	ft_init_draw(t_game *game)
{
	ft_set_pos(&game->cam.pos, game->data.start_pos.x, game->data.start_pos.y);
	ft_set_pos(&game->cam.dir, game->data.start_dir.x, game->data.start_dir.y);
	game->data.map[(int)game->data.start_pos.x][(int)game->data.start_pos.y]
		= '0';
	if (game->data.start_dir.y == 1)
		ft_set_pos(&game->cam.plane, -0.66, 0);
	else if (game->data.start_dir.y == -1)
		ft_set_pos(&game->cam.plane, 0.66, 0);
	else if (game->data.start_dir.x == 1)
		ft_set_pos(&game->cam.plane, 0, 0.66);
	else if (game->data.start_dir.x == -1)
		ft_set_pos(&game->cam.plane, 0, -0.66);
	game->cam.move_speed = MOVE_SPEED;
	game->cam.rot_speed = ROT_SPEED;
	if (ft_get_texture(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
