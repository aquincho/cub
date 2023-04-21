/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:53:52 by troberts          #+#    #+#             */
/*   Updated: 2023/04/09 18:47:42 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	clean_display(t_game *game, int return_code)
{
	if (game->mlx == NULL)
		return (return_code);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
	return (return_code);
}

int	clean_window_display(t_game *game, int return_code)
{
	if (game->win.ptr && game->mlx)
		mlx_destroy_window(game->mlx, game->win.ptr);
	return (clean_display(game, return_code));
}

int	clean_exit(t_game *game)
{
	free_data(&game->data);
	free_mlx(game);
	exit(EXIT_SUCCESS);
}
