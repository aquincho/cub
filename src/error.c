/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:30 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/18 11:12:26 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*msg_error(t_error error_type)
{
	if (error_type == sys_err)
		return ("System error");
	else if (error_type == arg_err)
		return ("Invalid number of arguments");
	else if (error_type == init_err)
		return ("Cannot initialize game");
	else if (error_type == rd_file_err)
		return ("Cannot read file: ");
	else if (error_type == file_err)
		return ("File error: ");
	else
		return ("Error");
}

int	display_error(t_error error_type, char *msg)
{
	char	*msg_err;

	msg_err = msg_error(error_type);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg_err, STDERR_FILENO);
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	error_exit(t_error error_type, char *msg, t_game *game, int return_code)
{
	display_error(error_type, msg);
	if (game)
		clean_exit(game);
	exit (return_code);
}
