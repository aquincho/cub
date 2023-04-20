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

static int	ft_update(t_game *game)
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

static int	ft_keypress(int keycode, t_game *game)
{
	int	player_move;

	player_move = 0;
	if (keycode == XK_Escape)
		clean_exit(game);
	if (keycode == XK_space)
		game->show_minimap = !game->show_minimap;
	if (keycode == XK_A || keycode == XK_a)
		player_move = ft_move_left_right(game, 1);
	else if (keycode == XK_D || keycode == XK_d)
		player_move = ft_move_left_right(game, -1);
	else if (keycode == XK_W || keycode == XK_w)
		player_move = ft_move_up_down(game, 1);
	else if (keycode == XK_S || keycode == XK_s)
		player_move = ft_move_up_down(game, -1);
	else if (keycode == XK_Left)
		player_move = ft_rotate_left(game);
	else if (keycode == XK_Right)
		player_move = ft_rotate_right(game);
	if (player_move)
		ft_update(game);
	return (0);
}

static int	ft_mouse(int x, int y, t_game *game)
{
	if (x <= game->mouse_x)
		ft_rotate_left(game);
	else
		ft_rotate_right(game);
	game->mouse_x = x;
	(void)y;
	return (EXIT_SUCCESS);
}

/* static int	ft_keyrelease(int keycode, t_game *game)
{
	int	player_move;

	if (keycode == K_A || keycode == K_D || keycode == K_W || keycode == K_S
		|| keycode == K_LT || keycode == K_RT)
	{
		player_move = 0;
		ft_update(game);
	}
	return (player_move);
} */

int	ft_game(t_game game)
{
	if (ft_init_mlx(&game))
		ft_error_exit(init_err, "Cannot initialize mlx", &game, EXIT_FAILURE);
	if (ft_init_draw(&game) == EXIT_FAILURE)
		ft_error_exit(init_err, "Cannot initialize draw", &game, EXIT_FAILURE);
	mlx_hook(game.win.ptr, DestroyNotify, StructureNotifyMask, clean_exit,
		&game);
	mlx_hook(game.win.ptr, KeyPress, KeyPressMask, ft_keypress, &game);
	mlx_hook(game.win.ptr, MotionNotify, PointerMotionMask, ft_mouse, &game);
	mlx_loop_hook(game.mlx, ft_draw, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
