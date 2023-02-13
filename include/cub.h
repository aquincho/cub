/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:08:09 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/13 13:02:48 by aquincho         ###   ########.fr       */
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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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
	t_color	ceil;
	t_color	floor;
}	t_map;

typedef struct	s_game
{
	t_map	*map;
}	t_game;

/* initialization init.c */
t_game	*ft_init_game(void);
t_map	*ft_init_map(void);
/* error management error.c*/
int	ft_error_exit(t_error error_type, char *msg);
/* free memory management free.c */
void	ft_free_game(t_game *game);

/* file parsing parser.c */
t_map	*ft_read_mapfile(char *arg);
/* parser utilities parser_utils.c */
int	ft_check_file(char *path, t_game *game);

#endif