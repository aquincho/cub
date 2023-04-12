/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:17:05 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/12 12:54:32 by aquincho         ###   ########.fr       */
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

	if (argc != 2)
		ft_error_exit(arg_err, NULL, NULL, EXIT_FAILURE);
	if (ft_init_game(&game))
		ft_error_exit(init_err, NULL, &game, EXIT_FAILURE);
	if (ft_read_file(&game, argv[1]))
		ft_error_exit(rd_file_err, NULL, &game, EXIT_FAILURE);
	ft_print_map(game);
	ft_game(game);
	clean_exit(&game);
	return (EXIT_SUCCESS);
}
