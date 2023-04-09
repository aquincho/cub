/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:53:26 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/09 18:19:36 by troberts         ###   ########.fr       */
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

static int	ft_keypress(int keycode, t_game *game)
{
	int	player_move;

	player_move = 0;
	if (keycode == K_ESC)
		ft_kill_win(game);
	else
	{
		if (keycode == K_A)
			player_move = ft_move_left_right(game, 1);
		if (keycode == K_D)
			player_move = ft_move_left_right(game, -1);
		if (keycode == K_W)
			player_move = ft_move_up_down(game, 1);
		if (keycode == K_S)
			player_move = ft_move_up_down(game, -1);
		if (keycode == K_LT)
			player_move = ft_rotate_left(game);
		if (keycode == K_RT)
			player_move = ft_rotate_right(game);
		if (player_move)
			ft_update(game);
	}
	return (0);
}

static int	ft_keyrelease(int keycode, t_game *game)
{
	int	player_move;

	if (keycode == K_A || keycode == K_D || keycode == K_W || keycode == K_S
		|| keycode == K_LT || keycode == K_RT)
	{
		player_move = 0;
		ft_update(game);
	}
	return (player_move);
}

int	ft_game(t_game game)
{
	if (ft_init_mlx(&game))
		ft_error_exit(init_err, "Cannot initialize mlx", &game, EXIT_FAILURE);
	if (ft_init_draw(&game) == EXIT_FAILURE)
		ft_error_exit(init_err, "Cannot initialize draw", &game, EXIT_FAILURE);
	ft_draw(&game);
	mlx_hook(game.win.ptr, 17, 1L << 17, clean_exit, &game);
	mlx_hook(game.win.ptr, 2, 1L << 0, ft_keypress, &game);
	mlx_hook(game.win.ptr, 3, 1L << 1, ft_keyrelease, &game);
	mlx_loop_hook(game.mlx, ft_draw, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
