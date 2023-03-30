/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:26:45 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 10:28:20 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_free_mlx(t_game *game)
{
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	if (game->win.ptr)
		mlx_destroy_window(game->mlx, game->win.ptr);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
	}
}

int	ft_kill_win(t_game *game)
{
	ft_free_mlx(game);
	if (game->mlx)
		free(game->mlx);
	ft_free_game(game);
	exit (0);
}
