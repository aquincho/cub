/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:53:26 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 09:33:57 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_game(t_game game)
{
	if (ft_init_mlx(&game))
		return (ft_error_exit(init_err, "Cannot initialize mlx", &game));
	ft_init_draw(&game);
	ft_draw(game);
	mlx_hook(game.win.ptr, 17, 1L << 17, ft_kill_win, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
