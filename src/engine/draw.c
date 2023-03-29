/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:01:27 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/29 15:38:02 by aquincho         ###   ########.fr       */
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

inline static void ft_init_ray_step(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist.x = (game->cam.pos.x - game->ray.map_x)
			* game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist.x = (game->ray.map_x + 1.0
			- game->cam.pos.x)
			* game->ray.delta_dist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist.y = (game->cam.pos.y - game->ray.map_y)
			* game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist.y = (game->ray.map_y + 1.0
			- game->cam.pos.y)
			* game->ray.delta_dist.y;
	}
}

inline static void ft_init_ray(t_game *game, int x)
{
	game->ray.cam_x = 2 * x / (game->win.size.x) - 1;
	game->ray.dir.x = game->cam.dir.x + game->cam.plane.x * game->ray.cam_x;
	game->ray.dir.y = game->cam.dir.y + game->cam.plane.y * game->ray.cam_x;
	game->ray.map_x = (int)game->cam.pos.x;
	game->ray.map_y = (int)game->cam.pos.y;
	if (game->ray.dir.x != 0)
		game->ray.delta_dist.x = fabs(1 / game->ray.dir.x);
	else
		game->ray.delta_dist.x = 0;
	if (game->ray.dir.y != 0)
		game->ray.delta_dist.y = fabs(1 / game->ray.dir.y);
	else
		game->ray.delta_dist.y = 0;
	ft_init_ray_step(game);
}
#include <stdio.h>
inline static void	ft_dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta_dist.x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta_dist.y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		printf("one step\n");
		if (game->data.map[game->ray.map_x][game->ray.map_y] != '0')
			hit = 1;
	}
}
#include <stdio.h>
void	ft_draw(t_game game)
{
	/*t_pos test;
	test.x = 100;
	test.y = 10;
	while (test.y < 300)
	{
		ft_pixel_put(&game.img, test, 0x00FF0000);
		test.y++;
	}*/
	int	x;

	x = 0;
	while (x < game.win.size.x)
	{
		ft_init_ray(&game, x);
		printf("init %f %f %f delta %f %f side %f %f step %d %d\n",
			game.ray.cam_x, game.ray.dir.x, game.ray.dir.y,
			game.ray.delta_dist.x, game.ray.delta_dist.y,
			game.ray.side_dist.x, game.ray.side_dist.y,
			game.ray.step_x, game.ray.step_y);
		ft_dda(&game);
		//printf("side dist %f / %f delta %f / %f map %d / %d\n step %d / %d", game.ray.side_dist.x,
		//game.ray.side_dist.y, game.ray.delta_dist.x, game.ray.delta_dist.y,
		//game.ray.map_x, game.ray.map_y, game.ray.step_x, game.ray.step_y);
		if (game.ray.side == 0)
		{
			game.ray.wall_dist = (game.ray.side_dist.x - game.ray.delta_dist.x);
			printf("side 0 %f / %f", game.ray.side_dist.x, game.ray.delta_dist.x);
		}
		else
		{
			game.ray.wall_dist = (game.ray.side_dist.y - game.ray.delta_dist.y);
			printf("side 1 %f / %f", game.ray.side_dist.y, game.ray.delta_dist.y);
		}
		game.ray.height = (int)(game.win.size.y / game.ray.wall_dist);
		int start = -game.ray.height / 2 + game.win.size.y / 2;
		if (start < 0)
			start = 0;
		int end = game.ray.height / 2 + game.win.size.y / 2;
		if (end > game.win.size.y)
			end = game.win.size.y - 1;
		int j;
		j = start;
		printf("win %f / %f wall %f height %d start %d end %d\n",
			game.win.size.x, game.win.size.y, game.ray.wall_dist, game.ray.height, start, end);
		while (j < end)
		{
			t_pos posline;
			posline.x = x;
			posline.y = j;
			ft_pixel_put(&game.img, posline, 0x00FF0000);
			j++;
		}
		x++;
	}
	mlx_put_image_to_window(game.mlx, game.win.ptr, game.img.ptr, 0, 0);
}