/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:01:27 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/05 16:36:34 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_init_wall(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir.x < 0)
			game->ray.tex_type = north;
		else
			game->ray.tex_type = south;
		game->ray.tex_wall_x = game->cam.pos.y + game->ray.wall_dist
			* game->ray.dir.y;
	}
	if (game->ray.side == 1)
	{
		if (game->ray.dir.x < 0)
			game->ray.tex_type = east;
		else
			game->ray.tex_type = west;
		game->ray.tex_wall_x = game->cam.pos.x + game->ray.wall_dist
			* game->ray.dir.x;
	}
	game->ray.tex_wall_x -= floor((game->ray.tex_wall_x));
	game->ray.tex_pos.x = (int)(game->ray.tex_wall_x
		* game->texture[game->ray.tex_type].width);
	if ((game->ray.side == 0 && game->ray.dir.x > 0)
		|| (game->ray.side == 1 && game->ray.dir.x < 0))
		game->ray.tex_pos.x = game->texture[game->ray.tex_type].width
			- game->ray.tex_pos.x - 1;
}
#include <stdio.h>
void	ft_draw_wall(t_game *game, t_pos *pos)
{
	int	i;

	ft_init_wall(game);
	game->ray.tex_step = 1.0 * game->texture[game->ray.tex_type].height
		/ game->ray.height;

	/*game->ray.tex_pos.y = (int)((pos.y * 2 - game->win.size.y
		+ game->ray.height));
	ft_pixel_put(&game->img, pos,
		ft_get_tex_color(&game->texture[game->ray.tex_type],
		&game->ray.tex_pos));*/
	/*if (game->ray.side == 0)
	{
		if (game->ray.dir.x < 0)
			ft_pixel_put(&game->img, pos, 0x00FF0000);
		else
			ft_pixel_put(&game->img, pos, 0x000000FF);
	}
	else
	{
		if (game->ray.dir.y < 0)
			ft_pixel_put(&game->img, pos, 0x0000FF00);
		else
			ft_pixel_put(&game->img, pos, 0x00FF00FF);
	}*/
}

void	ft_draw_column(t_game *game, int x)
{
	t_pos	pos;

	game->ray.wall_start.x = x;
	game->ray.wall_end.x = x;
	game->ray.wall_start.y = -game->ray.height / 2 + game->win.size.y /2;
	if (game->ray.wall_start.y < 0)
		game->ray.wall_start.y = 0;
	game->ray.wall_end.y = game->ray.height / 2 + game->win.size.y / 2;
	if (game->ray.wall_end.y >= game->win.size.y)
		game->ray.wall_end.y = game->win.size.y - 1;
	pos.x = x;
	pos.y = 0;
	while (pos.y < game->win.size.y)
	{
		if (pos.y < game->ray.wall_start.y)
			ft_pixel_put(&game->img, pos, ft_rgb_to_int(game->data.ceil.r,
				game->data.ceil.g, game->data.ceil.b));
		else if (pos.y < game->ray.wall_end.y)
			ft_draw_wall(game, &pos);
		else
			ft_pixel_put(&game->img, pos, ft_rgb_to_int(game->data.floor.r,
				game->data.floor.g, game->data.floor.b));
		pos.y += 1;
	}
	//ft_draw_wall(game, pos);
}

int	ft_draw(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->win.size.x)
	{
		ft_raycast(game, x);
		ft_draw_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win.ptr, game->img.ptr, 0, 0);
	return (EXIT_SUCCESS);
}
