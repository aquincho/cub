/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:16 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/29 11:22:58 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return (EXIT_SUCCESS);
	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free (tab);
	return (EXIT_SUCCESS);
}

int	ft_free_data(t_data *data)
{
	int	i;

	if (!data)
		return (0);
	if (data->name)
		free (data->name);
	if (data->map)
		ft_free_tab(data->map);
	i = -1;
	while (++i < NB_TEXTURES)
		free(data->texture[i]);
	return (0);
}

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

int	ft_free_game(t_game *game)
{
	if (!game)
		return (0);
	if (&game->data)
		ft_free_data(&game->data);
	return (0);
}