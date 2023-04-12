/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:26:41 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/12 10:56:28 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_pixel_put(t_img *img, t_pos pos, int color)
{
	*(int *)(img->addr
		+ (img->line_len * (int)pos.y) + ((int)pos.x * img->bpp / 8))
		= color;
}

int	ft_rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	ft_get_tex_color(t_texture *tex, t_pos *pos)
{
	if (pos->x >= 0 && pos->x < tex->width
		&& pos->y >= 0 && pos->y < tex->height)
	{
		return (*(int *)(tex->addr
			+ (4 * tex->width * (int)pos->y)
			+ (4 * (int)pos->x)));
	}
	return (0x0);
}
