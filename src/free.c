/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:16 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/01 10:28:26 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return (EXIT_SUCCESS);
	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free (tab);
	return (EXIT_SUCCESS);
}

int	ft_free_data(t_data *data)
{
	int	i;

	if (!data)
		return (0);
	if (data->name)
		free (data->name);
	if (data->map)
		ft_free_tab(data->map);
	i = -1;
	while (++i < NB_TEXTURES)
		free(data->texture[i]);
	return (0);
}

int	ft_free_game(t_game *game)
{
	if (!game)
		return (0);
	if (&game->data)
		ft_free_data(&game->data);
	return (0);
}