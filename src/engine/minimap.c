/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:27:49 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/12 14:15:10 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pos	ft_size_mmap(t_game *game)
{
	t_pos	m_size;

	m_size.x = game->data.width * MMAP_RATIO - MMAP_RATIO;
	m_size.y = game->data.height * MMAP_RATIO;
	if (m_size.x > 300)
		m_size.x = 300;
	if (m_size.y > 200)
		m_size.y = 200;
	return (m_size);
}

void	ft_draw_minimap(t_game *game)
{
	t_pos	pos;
	t_pos	m_size;

	m_size = ft_size_mmap(game);
	pos.x = 0;
	while (pos.x < m_size.x)
	{
		pos.y = 0;
		while (pos.y < m_size.y)
		{
			if (pos.x < ft_strlen(game->data.map[(int)floor(pos.y / 8)]) * 8
				&& game->data.map[(int)floor(pos.y / 8)][(int)floor(pos.x / 8)]
				== '1')
				ft_pixel_put(&game->img_minimap, pos,
					ft_rgb_to_int(200, 50, 50));
			else if (pos.x
				< ft_strlen(game->data.map[(int)floor(pos.y / 8)]) * 8
				&& game->data.map[(int)floor(pos.y / 8)][(int)floor(pos.x / 8)]
				== '0')
				ft_pixel_put(&game->img_minimap, pos,
					ft_rgb_to_int(100, 100, 100));
			else
				ft_pixel_put(&game->img_minimap, pos, ft_rgb_to_int(0, 0, 0));
			if (pos.x > (game->cam.pos.x * 8) - 2
				&& pos.x < (game->cam.pos.x * 8) + 2
				&& pos.y > (game->cam.pos.y * 8) - 2
				&& pos.y < (game->cam.pos.y * 8) + 2)
				ft_pixel_put(&game->img_minimap, pos, ft_rgb_to_int(250, 250, 250));
			pos.y += 1;
		}
		pos.x += 1;
	}
}
