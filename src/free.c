/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:16 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/27 09:46:16 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_free_data(t_data *data)
{
	if (!data)
		return (0);
	if (data->name)
		free (data->name);
	if (data->map)
		free(data->map);
	free (data);
	return (0);
}

int	ft_free_game(t_game *game)
{
	if (!game)
		return (0);
	if (&game->data)
		ft_free_data(&game->data);
	free(game);
	return (0);
}