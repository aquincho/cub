/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:16 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/17 09:18:25 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_free_map(t_map *map)
{
	if (!map)
		return (0);
	if (map->name)
		free (map->name);
	if (map->map)
		free(map->map);
	free (map);
	return (0);
}

int	ft_free_game(t_game *game)
{
	if (!game)
		return (0);
	if (game->map)
		ft_free_map(game->map);
	free(game);
	return (0);
}