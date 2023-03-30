/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:39:57 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/30 11:29:29 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_set_pos(t_pos *pos, double X, double Y)
{
	pos->x = X;
	pos->y = Y;
}

int	ft_check_inset(char *line, char *set)
{
	int		i;
	int		j;
	bool	not_in_set;

	i = 0;
	while (line[i])
	{
		not_in_set = true;
		j = 0;
		while (set[j])
		{
			if (line[i] == set[j])
				not_in_set = false;
			j++;
		}
		if (not_in_set)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
