/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:17:05 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/09 09:49:02 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>
int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	if (argc < 2)
		return(ft_error(arg_err, NULL));
	if (ft_init_game(&game))
		return (ft_error(init_err, " Cannot initialize game"));
	i = 0;
	while (argv[++i])
	{
		if (ft_read_file(&game, argv[i]))
			return (EXIT_FAILURE);
		ft_game(&game);
	}
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
	ft_free_game(&game);
	return (EXIT_SUCCESS);
}

/* TODO modif parser  decomposer conditions pour liberer tmp quand erreur */
/* TODO modif nom fonction tabdup_addline */