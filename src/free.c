/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:16 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/12 13:25:08 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return (EXIT_SUCCESS);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free (tab);
	tab = NULL;
	return (EXIT_SUCCESS);
}

int	free_texture(char **texture)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		if (texture[i])
			free (texture[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	free_data(t_data *data)
{
	if (!data)
		return (0);
	if (data->name)
		free (data->name);
	if (data->map)
		free_tab(data->map);
	free_texture(data->texture);
	return (0);
}

int	free_game(t_game *game)
{
	if (!game)
		return (0);
	free_data(&game->data);
	return (0);
}
