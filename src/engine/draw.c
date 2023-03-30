/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:01:27 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 09:35:01 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_init_draw(t_game *game)
{
	ft_set_pos(&game->cam.pos, game->data.start_pos.x, game->data.start_pos.y);
	ft_set_pos(&game->cam.dir, game->data.start_dir.x, game->data.start_dir.y);
	if (game->data.start_dir.y == 1)
		ft_set_pos(&game->cam.plane, -0.66, 0);
	else if (game->data.start_dir.y == -1)
		ft_set_pos(&game->cam.plane, 0.66, 0);
	else if (game->data.start_dir.x == 1)
		ft_set_pos(&game->cam.plane, 0, 0.66);
	else if (game->data.start_dir.x == -1)
		ft_set_pos(&game->cam.plane, 0, -0.66);
}

void	ft_draw(t_game game)
{
	int		x;
	int		start;
	int		end;
	int		i;
	t_pos	posline;

	x = 0;
	while (x < game.win.size.x)
	{
		ft_raycast(&game, x);
		start = -game.ray.height / 2 + game.win.size.y / 2;
		if (start < 0)
			start = 0;
		end = game.ray.height / 2 + game.win.size.y / 2;
		if (end > game.win.size.y)
			end = game.win.size.y - 1;
		posline.x = x;
		i = start;
		while (i < end)
		{
			posline.y = i;
			if (game.ray.side == 0)
			{
				if (game.ray.dir.x < 0)
					ft_pixel_put(&game.img, posline, 0x00FF0000);
				else
					ft_pixel_put(&game.img, posline, 0x000000FF);
			}
			else
			{
				if (game.ray.dir.y < 0)
					ft_pixel_put(&game.img, posline, 0x0000FF00);
				else
					ft_pixel_put(&game.img, posline, 0x00FF00FF);
			}
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(game.mlx, game.win.ptr, game.img.ptr, 0, 0);
}
