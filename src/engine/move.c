/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:54:34 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/07 11:47:09 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_move_up_down(t_game *game, int direction)
{
	if (game->data.map[(int)(game->cam.pos.x + direction * game->cam.dir.x
			* game->cam.move_speed)][(int)game->cam.pos.y] == '0' &&
			game->data.map[(int)(game->cam.pos.x)][(int)(game->cam.pos.y +
			direction * game->cam.dir.y * game->cam.move_speed)] == '0')
	{
		game->cam.pos.x += direction * game->cam.dir.x * game->cam.move_speed;
		game->cam.pos.y += direction * game->cam.dir.y * game->cam.move_speed;
	}
	return (1);
}

int	ft_move_left_right(t_game *game, int direction)
{
	if (game->data.map[(int)(game->cam.pos.x + direction * game->cam.dir.y
			* game->cam.move_speed)][(int)game->cam.pos.y] == '0' &&
			game->data.map[(int)(game->cam.pos.x)][(int)(game->cam.pos.y -
			direction * game->cam.dir.x * game->cam.move_speed)] == '0')
	{
		game->cam.pos.x += direction * game->cam.dir.y * game->cam.move_speed;
		game->cam.pos.y -= direction * game->cam.dir.x * game->cam.move_speed;
	}
	return (1);
}

int	ft_rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->cam.dir.x;
	game->cam.dir.x = game->cam.dir.x * cos(-game->cam.rot_speed)
		- game->cam.dir.y * sin(-game->cam.rot_speed);
	game->cam.dir.y = old_dir_x * sin(-game->cam.rot_speed)
		+ game->cam.dir.y * cos(-game->cam.rot_speed);
	old_plane_x = game->cam.plane.x;
	game->cam.plane.x = game->cam.plane.x * cos(-game->cam.rot_speed)
		- game->cam.plane.y * sin(-game->cam.rot_speed);
	game->cam.plane.y = old_plane_x * sin(-game->cam.rot_speed)
		+ game->cam.plane.y * cos(-game->cam.rot_speed);
	return (1);
}

int	ft_rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->cam.dir.x;
	game->cam.dir.x = game->cam.dir.x * cos(game->cam.rot_speed)
		- game->cam.dir.y * sin(game->cam.rot_speed);
	game->cam.dir.y = old_dir_x * sin(game->cam.rot_speed)
		+ game->cam.dir.y * cos(game->cam.rot_speed);
	old_plane_x = game->cam.plane.x;
	game->cam.plane.x = game->cam.plane.x * cos(game->cam.rot_speed)
		- game->cam.plane.y * sin(game->cam.rot_speed);
	game->cam.plane.y = old_plane_x * sin(game->cam.rot_speed)
		+ game->cam.plane.y * cos(game->cam.rot_speed);
	return (1);
}
