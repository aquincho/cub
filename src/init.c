/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:23:57 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/17 09:21:24 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_color	ft_init_color(int n)
{
	t_color	result;
	
	result.r = n;
	result.g = n;
	result.b = n;
	return (result);
}

int	ft_init_map(t_map *map)
{
	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_error(sys_err, NULL));
	map->name = NULL;
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->n_wall = NULL;
	map->s_wall = NULL;
	map->e_wall = NULL;
	map->w_wall = NULL;
	map->ceil = ft_init_color(0);
	map->floor = ft_init_color(0);
	return (0);
}

int	ft_init_game(t_game *game)
{
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_error(sys_err, NULL));
	if (ft_init_map(game->map))
		return (ft_error(sys_err, NULL));
	game->exit_status = EXIT_SUCCESS;
	return (game->exit_status);
}