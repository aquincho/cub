/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:53:26 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/18 11:18:25 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	update(t_game *game)
{
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	game->img.ptr = mlx_new_image(game->mlx, game->win.size.x,
			game->win.size.y);
	if (!game->img.ptr)
		return (EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	return (EXIT_SUCCESS);
}

static int	keypress(int keycode, t_game *game)
{
	int	player_move;

	player_move = 0;
	if (keycode == XK_Escape)
		clean_exit(game);
	if (keycode == XK_space)
		game->show_minimap = !game->show_minimap;
	if (keycode == XK_A || keycode == XK_a)
		player_move = move_left_right(game, 1);
	else if (keycode == XK_D || keycode == XK_d)
		player_move = move_left_right(game, -1);
	else if (keycode == XK_W || keycode == XK_w)
		player_move = move_up_down(game, 1);
	else if (keycode == XK_S || keycode == XK_s)
		player_move = move_up_down(game, -1);
	else if (keycode == XK_Left)
		player_move = rotate_left(game);
	else if (keycode == XK_Right)
		player_move = rotate_right(game);
	if (player_move)
		update(game);
	return (0);
}

static int	mouse(int x, int y, t_game *game)
{
	if (x <= game->mouse_x)
		rotate_left(game);
	else
		rotate_right(game);
	game->mouse_x = x;
	(void)y;
	return (EXIT_SUCCESS);
}

/* static int	keyrelease(int keycode, t_game *game)
{
	int	player_move;

	if (keycode == K_A || keycode == K_D || keycode == K_W || keycode == K_S
		|| keycode == K_LT || keycode == K_RT)
	{
		player_move = 0;
		update(game);
	}
	return (player_move);
} */

int	game(t_game game)
{
	if (init_mlx(&game))
		error_exit(init_err, "Cannot initialize mlx", &game, EXIT_FAILURE);
	if (init_draw(&game) == EXIT_FAILURE)
		error_exit(init_err, "Cannot initialize draw", &game, EXIT_FAILURE);
	mlx_hook(game.win.ptr, DestroyNotify, StructureNotifyMask, clean_exit,
		&game);
	mlx_hook(game.win.ptr, KeyPress, KeyPressMask, keypress, &game);
	mlx_hook(game.win.ptr, MotionNotify, PointerMotionMask, mouse, &game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
