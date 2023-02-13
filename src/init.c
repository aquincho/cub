/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:23:57 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 11:15:07 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map	*ft_init_map(void)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (!resut)
		ft_error_exit(sys_err, "Cannot create map");
	result->map = NULL;
	return (result);
}

t_game	*ft_init_game(void)
{
	t_game	*result;

	result = malloc(sizeof(t_game));
	if (!result)
		ft_error_exit(sys_err, "Cannot create game");
	game->map = ft_init_map();
	return (result);
}