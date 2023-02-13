/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:08:09 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 11:45:53 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#include "libft.h"

typedef enum e_error
{
	sys_err,
	filetype_err,
	default_err
}	t_error;

typedef struct s_map
{
	char	*name;
	char	**map;
	int		width;
	int		length;
	char	*n_wall;
	char	*s_wall;
	char	*e_wall;
	char	*w_wall;
	int		ceil[3];
	int		floor[3];
}	t_map;

typedef struct	s_game
{
	t_map	*map;
}	t_game;

/* initialization init.c */
t_game	*ft_init_game(void);
t_map	*ft_init_map(void);

int	ft_error_exit(t_error error_type, char *msg);

void	ft_free_game(t_game *game);

t_map	*ft_read_mapfile(char *arg);

#endif