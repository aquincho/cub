/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:26:45 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/18 11:10:58 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_free_mlx(t_game *game)
{
	int	i;

	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	if (game->img_minimap.ptr)
		mlx_destroy_image(game->mlx, game->img_minimap.ptr);
	i = 0;
	while (i < NB_TEXTURES)
	{
		if (game->texture[i].ptr)
			mlx_destroy_image(game->mlx, game->texture[i].ptr);
		i++;
	}
	if (game->win.ptr)
		mlx_destroy_window(game->mlx, game->win.ptr);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
}

int	ft_kill_win(t_game *game)
{
	ft_free_mlx(game);
	ft_free_game(game);
	exit (0);
}
