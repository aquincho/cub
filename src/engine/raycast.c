/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:56:12 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/12 11:42:50 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

inline static void	ft_init_ray_step_y(t_game *game)
{
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

inline static void	ft_init_ray_step_x(t_game *game)
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
	ft_init_ray_step_y(game);
}

inline static void	ft_init_ray(t_game *game, int x)
{
	game->ray.cam_x = 2 * x / (game->win.size.x) - 1;
	game->ray.dir.x = game->cam.dir.x + game->cam.plane.x * game->ray.cam_x;
	game->ray.dir.y = game->cam.dir.y + game->cam.plane.y * game->ray.cam_x;
	game->ray.map_x = (int)game->cam.pos.x;
	game->ray.map_y = (int)game->cam.pos.y;
	if (game->ray.dir.x != 0)
		game->ray.delta_dist.x = fabs(1 / game->ray.dir.x);
	else
		game->ray.delta_dist.x = FLT_MAX;
	if (game->ray.dir.y != 0)
		game->ray.delta_dist.y = fabs(1 / game->ray.dir.y);
	else
		game->ray.delta_dist.y = FLT_MAX;
	ft_init_ray_step_x(game);
}

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
		if (game->data.map[game->ray.map_y][game->ray.map_x] != '0')
			hit = 1;
	}
}

void	ft_raycast(t_game *game, int x)
{
	ft_init_ray(game, x);
	ft_dda(game);
	if (game->ray.side == 0)
		game->ray.wall_dist = (game->ray.side_dist.x - game->ray.delta_dist.x);
	else
		game->ray.wall_dist = (game->ray.side_dist.y - game->ray.delta_dist.y);
	game->ray.height = (int)(game->win.size.y / game->ray.wall_dist);
}
