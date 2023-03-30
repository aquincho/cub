/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:23:57 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 09:24:34 by aquincho         ###   ########.fr       */
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

static int	ft_init_map(t_data *data)
{
	int	i;

	data->name = NULL;
	data->map = NULL;
	data->width = 0;
	data->height = 0;
	ft_set_pos(&data->start_pos, 0, 0);
	ft_set_pos(&data->start_dir, 0, 0);
	i = -1;
	while (++i < 4)
		data->texture[i] = NULL;
	data->ceil = ft_init_color(0);
	data->floor = ft_init_color(0);
	return (EXIT_SUCCESS);
}

int	ft_init_game(t_game *game)
{
	game->exit_status = EXIT_SUCCESS;
	if (ft_init_map(&game->data))
		return (ft_error(sys_err, NULL));
	game->mlx = NULL;
	return (game->exit_status);
}
