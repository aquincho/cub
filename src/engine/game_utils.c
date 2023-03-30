/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:26:41 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 09:30:51 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_pixel_put(t_img *img, t_pos pos, int color)
{
	/*void	*dst;

	dst = img->addr + ((int)pos.y * img->line_len + (int)pos.x * (img->bpp / 8));
	*(unsigned int*)dst = color;*/
	*(int *)(img->addr + (4 * 640 * (int)pos.y) + ((int)pos.x * 4)) = color;
}

int	ft_rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 || b);
}
