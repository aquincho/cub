/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:17:05 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/17 09:51:44 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit(arg_err, NULL, NULL, EXIT_FAILURE);
	if (init_game(&game))
		error_exit(init_err, NULL, &game, EXIT_FAILURE);
	if (read_file(&game, argv[1]))
		error_exit(rd_file_err, NULL, &game, EXIT_FAILURE);
	game(game);
	clean_exit(&game);
	return (EXIT_SUCCESS);
}
