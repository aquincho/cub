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
		ft_error_exit(arg_err, NULL, NULL, EXIT_FAILURE);
	if (ft_init_game(&game))
		ft_error_exit(init_err, NULL, &game, EXIT_FAILURE);
	if (ft_read_file(&game, argv[1]))
		ft_error_exit(rd_file_err, NULL, &game, EXIT_FAILURE);
	ft_game(game);
	clean_exit(&game);
	return (EXIT_SUCCESS);
}
