/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:53:26 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/04 12:17:52 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_update(t_game *game)
{
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	game->img.ptr = mlx_new_image(game->mlx, game->win.size.x,
			game->win.size.y);
	if (!game->img.ptr)
		return (EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_len, &game->img.line_len);
	return (EXIT_SUCCESS);
}

int	ft_move_left(t_game *game)
{
		game->cam.pos.x += game->ray.dir.x * game->ray.move_speed;
		game->cam.pos.y += game->ray.dir.y * game->ray.move_speed;
	return (1);
}

int	ft_rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->ray.dir.x;
	game->ray.dir.x = game->ray.dir.x * cos(-game->ray.rot_speed)
		- game->ray.dir.y  * sin(-game->ray.rot_speed);
	game->ray.dir.y = old_dir_x * sin(-game->ray.rot_speed)
		+ game->ray.dir.y * cos(-game->ray.rot_speed);
	old_plane_x = game->cam.plane.x;
	game->cam.plane.x = game->cam.plane.x * cos(-game->ray.rot_speed)
		- game->cam.plane.y * sin(-game->ray.rot_speed);
	game->cam.plane.y = old_plane_x * sin(-game->ray.rot_speed)
		+ game->cam.plane.y * cos(-game->ray.rot_speed);
	return (1);
}

static int	ft_keypress(int keycode, t_game *game)
{
	int	player_move;

	if (keycode == K_ESC)
		ft_kill_win(game);
	else
	{
		if (keycode == K_A)
			player_move = ft_move_left(game);
		if (keycode == K_LT)
			player_move = ft_rotate_left(game);
		if (player_move)
			ft_update(game);
	}
	return (0);
}

int	ft_game(t_game game)
{
	if (ft_init_mlx(&game))
		return (ft_error_exit(init_err, "Cannot initialize mlx", &game));
	ft_init_draw(&game);
	ft_draw(&game);
	mlx_hook(game.win.ptr, 17, 1L << 17, ft_kill_win, &game);
	mlx_hook(game.win.ptr, 2, 1L << 0, ft_keypress, &game);
	mlx_loop_hook(game.mlx, ft_draw, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
