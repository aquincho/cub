/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:45:41 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 09:32:49 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (EXIT_FAILURE);
	ft_set_pos(&game->win.size, (double)WIN_WIDTH, (double)WIN_HEIGHT);
	game->win.ptr = mlx_new_window(game->mlx, game->win.size.x,
			game->win.size.y, "CUB3D");
	if (!game->win.ptr)
		return (EXIT_FAILURE);
	game->img.ptr = mlx_new_image(game->mlx, game->win.size.x,
			game->win.size.y);
	if (!game->img.ptr)
		return (EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_len, &game->img.line_len);
	return (0);
}
