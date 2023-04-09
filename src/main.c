/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:17:05 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/09 17:44:38 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#include <stdio.h>
void ft_print_map(t_game game)
{
	int j;

	j = 0;
	while (game.data.map[j])
	{
		printf("%s\n",game.data.map[j]);
		j++;
	}
	printf("%d - %d\n", game.data.width, game.data.height);
	j = -1;
	while (++j < 4)
		printf("%s\n", game.data.texture[j]);
	printf("ceil r:%d - g:%d - b:%d\n", game.data.ceil.r,
		game.data.ceil.g, game.data.ceil.b);
	printf("floor r:%d - g:%d - b:%d\n", game.data.floor.r,
		game.data.floor.g, game.data.floor.b);
	printf("pos %f %f dir %f %f", game.data.start_pos.x, game.data.start_pos.y,
		game.data.start_dir.x, game.data.start_dir.y);
}

int	main(int argc, char **argv)
{
	t_game	game;

	printf("Start\n");
	if (argc != 2)
		return (ft_display_error(arg_err, NULL));
	if (ft_init_game(&game))
		return (ft_display_error(init_err, " Cannot initialize game"));
	if (ft_read_file(&game, argv[1]))
	{
		ft_free_game(&game);
		return (EXIT_FAILURE);
	}
	ft_print_map(game);
	ft_game(game);
	ft_kill_win(&game);
	return (EXIT_SUCCESS);
}
