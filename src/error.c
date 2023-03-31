/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:30 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/31 10:35:40 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*ft_msg_error(t_error error_type)
{
	if (error_type == sys_err)
		return ("System error");
	else if (error_type == arg_err)
		return ("Invalid number of arguments");
	else if (error_type == init_err)
		return ("Cannot initialize game");
	else if (error_type == rd_file_err)
		return ("cannot read file: ");
	else if (error_type == file_err)
		return ("File error: ");
	else
		return ("default error");
}

int	ft_error(t_error error_type, char *msg)
{
	char	*msg_err;

	msg_err = ft_msg_error(error_type);
	(void)write(2, "cub3d: error: ", 14);
	(void)write(2, msg_err, ft_strlen(msg_err));
	if (msg)
		(void)write(2, msg, ft_strlen(msg));
	(void)write(2, "\n", 1);
	return (error_type);
}

int	ft_error_exit(t_error error_type, char *msg, t_game *game)
{
	char	*msg_err;

	msg_err = ft_msg_error(error_type);
	(void)write(2, "cub3d: error: ", 14);
	(void)write(2, msg_err, ft_strlen(msg_err));
	if (msg)
		(void)write(2, msg, ft_strlen(msg));
	(void)write(2, "\n", 1);
	ft_free_game(game);
	exit (error_type);
}
