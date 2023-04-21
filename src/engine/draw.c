/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:01:27 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/18 11:07:48 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_wall(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir.x < 0)
			game->ray.tex_type = west;
		else
			game->ray.tex_type = east;
		game->ray.tex_wall_x = game->cam.pos.y + game->ray.wall_dist
			* game->ray.dir.y;
	}
	if (game->ray.side == 1)
	{
		if (game->ray.dir.y < 0)
			game->ray.tex_type = north;
		else
			game->ray.tex_type = south;
		game->ray.tex_wall_x = game->cam.pos.x + game->ray.wall_dist
			* game->ray.dir.x;
	}
	game->ray.tex_wall_x -= floor((game->ray.tex_wall_x));
	game->ray.tex_pos_int.x = (int)(game->ray.tex_wall_x
			* game->texture[game->ray.tex_type].width);
	if ((game->ray.side == 0 && game->ray.dir.x > 0)
		|| (game->ray.side == 1 && game->ray.dir.y < 0))
		game->ray.tex_pos_int.x = game->texture[game->ray.tex_type].width
			- game->ray.tex_pos_int.x - 1;
}

void	draw_wall(t_game *game, t_pos pos)
{
	init_wall(game);
	game->ray.tex_step = 1.0 * game->texture[game->ray.tex_type].height
		/ game->ray.height;
	game->ray.tex_pos.y = (game->ray.wall_start.y - game->win.size.y / 2
			+ game->ray.height / 2) * game->ray.tex_step;
	pos.y = game->ray.wall_start.y;
	while (pos.y <= game->ray.wall_end.y)
	{
		game->ray.tex_pos_int.y = (int)game->ray.tex_pos.y
			& (game->texture[game->ray.tex_type].height - 1);
		game->ray.tex_pos.y += game->ray.tex_step;
		pixel_put(&game->img, pos,
			get_tex_color(&game->texture[game->ray.tex_type],
				&game->ray.tex_pos_int));
		pos.y += 1;
	}
}

void	draw_column(t_game *game, int x)
{
	t_pos	pos;

	game->ray.wall_start.x = x;
	game->ray.wall_end.x = x;
	game->ray.wall_start.y = -game->ray.height / 2 + game->win.size.y / 2;
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
		else if (pos.y > game->ray.wall_end.y)
			ft_pixel_put(&game->img, pos, ft_rgb_to_int(game->data.floor.r,
					game->data.floor.g, game->data.floor.b));
		pos.y += 1;
	}
	draw_wall(game, pos);
}

int	draw(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->win.size.x)
	{
		raycast(game, x);
		draw_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win.ptr, game->img.ptr, 0, 0);
	if (game->show_minimap)
	{
		if (game->mmap_ratio >= 1)
		{
			draw_minimap(game);
			mlx_put_image_to_window(game->mlx, game->win.ptr,
				game->img_minimap.ptr, 10, 10);
		}
		else
			mlx_string_put(game->mlx, game->win.ptr, 10, 10,
				ft_rgb_to_int(250, 10, 10), "MAP IS TOO LARGE TO BE SHOWED");
	}
	return (EXIT_SUCCESS);
}
