/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:30 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 12:31:33 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_error_exit(t_error error_type, char *msg)
{
	write(2, msg, ft_strlen(msg));
	(void)error_type;
	exit (1);
}