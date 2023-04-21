/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:27:49 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/18 09:09:16 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	size_mmap(t_game *game)
{
	game->mmap_size.x = game->data.width * MMAP_RATIO;
	game->mmap_size.y = game->data.height * MMAP_RATIO;
	if (game->mmap_size.x > WIN_WIDTH / 2)
		game->mmap_size.x = WIN_WIDTH / 2;
	if (game->mmap_size.y > WIN_HEIGHT / 2)
		game->mmap_size.y = WIN_HEIGHT / 2;
	if (game->data.width * MMAP_RATIO > WIN_WIDTH / 2
		|| game->data.height * MMAP_RATIO > WIN_HEIGHT / 2)
	{
		game->mmap_ratio = (int)fmin(WIN_WIDTH / (2 * game->data.width),
				WIN_HEIGHT / (2 * game->data.height));
	}
	else
		game->mmap_ratio = MMAP_RATIO;
	if (game->mmap_ratio < 1)
		game->mmap_ratio = -1;
	else
	{
		game->mmap_size.x = game->data.width * game->mmap_ratio;
		game->mmap_size.y = game->data.height * game->mmap_ratio;
	}
}

void	draw_minimap_elements(t_game *game, t_pos pos)
{
	if (pos.x < game->data.width * game->mmap_ratio
		&& pos.y < game->data.height * game->mmap_ratio
		&& pos.x
		< ft_strlen(game->data.map[(int)floor(pos.y / game->mmap_ratio)])
		* game->mmap_ratio
		&& game->data.map[(int)floor(pos.y / game->mmap_ratio)]
		[(int)floor(pos.x / game->mmap_ratio)] == '1')
		ft_pixel_put(&game->img_minimap, pos,
			ft_rgb_to_int(200, 50, 50));
	else if (pos.x < game->data.width * game->mmap_ratio
		&& pos.y < game->data.height * game->mmap_ratio
		&& pos.x
		< ft_strlen(game->data.map[(int)floor(pos.y / game->mmap_ratio)])
		* game->mmap_ratio
		&& game->data.map[(int)floor(pos.y / game->mmap_ratio)]
		[(int)floor(pos.x / game->mmap_ratio)] == '0')
		ft_pixel_put(&game->img_minimap, pos,
			ft_rgb_to_int(100, 100, 100));
	else
		ft_pixel_put(&game->img_minimap, pos, ft_rgb_to_int(0, 0, 0));
}

void	draw_minimap(t_game *game)
{
	t_pos	pos;

	pos.x = 0;
	while (pos.x < game->mmap_size.x)
	{
		pos.y = 0;
		while (pos.y < game->mmap_size.y)
		{
			draw_minimap_elements(game, pos);
			if (pos.x > (game->cam.pos.x * game->mmap_ratio) - 2
				&& pos.x < (game->cam.pos.x * game->mmap_ratio) + 2
				&& pos.y > (game->cam.pos.y * game->mmap_ratio) - 2
				&& pos.y < (game->cam.pos.y * game->mmap_ratio) + 2)
				ft_pixel_put(&game->img_minimap, pos,
					ft_rgb_to_int(250, 250, 250));
			pos.y += 1;
		}
		pos.x += 1;
	}
}
