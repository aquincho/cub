/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:50:20 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 11:51:46 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_check_file(char *path, t_game *game)
{
	int	result;
	int	tmp_fd;

	result = 0;
	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd > 0)
		close (tmp_fd);
	else
	{
		ft_error_exit(filetype, "Wrong image file");
	}
	return (result);
}