/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:26:41 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/05 15:58:42 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_pixel_put(t_img *img, t_pos pos, int color)
{
	/*void	*dst;

	dst = img->addr + ((int)pos.y * img->line_len + (int)pos.x * (img->bpp / 8));
	*(unsigned int*)dst = color;*/
	*(int *)(img->addr + (4 * WIN_WIDTH * (int)pos.y) + ((int)pos.x * 4))
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
		return (*(int*)(tex->ptr
			+ (4 * tex->width * (int)pos->y)
			+ (4 * (int)pos->x)));
	}
	return (0x0);
}