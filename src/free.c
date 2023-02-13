/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:16 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 11:37:20 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->name)
		free (map->name);
	if (map->map)
		free(map->map);
	free (map);
}

void	ft_free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		ft_free_map(game->map);
	free(game);
}