/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:17:05 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/27 12:10:15 by aquincho         ###   ########.fr       */
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
	}
	int j;
	j = 0;
	while (game.data.map[j])
	{
		printf("%s\n",game.data.map[j]);
		j++;
	}
	printf("%d - %d", game.data.width, game.data.height);
	//ft_free_game(&game);
	return (EXIT_SUCCESS);
}