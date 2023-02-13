/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:23:57 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 12:52:59 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map	*ft_init_map(void)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (!result)
		ft_error_exit(sys_err, "Cannot create map");
	result->name = NULL;
	result->map = NULL;
	result->width = 0;
	result->height = 0;
	result->ceil.r = 0;
	result->ceil.g = 0;
	result->ceil.b = 0;
	return (result);
}

t_game	*ft_init_game(void)
{
	t_game	*result;

	result = malloc(sizeof(t_game));
	if (!result)
		ft_error_exit(sys_err, "Cannot create game");
	result->map = ft_init_map();
	return (result);
}