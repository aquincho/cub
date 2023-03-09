/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:08:09 by aquincho          #+#    #+#             */
/*   Updated: 2023/03/09 09:06:49 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
//# include <mlx.h>
# include "../mlx/mlx.h"

# define NB_TEXTURES	4
# define MAP_CHAR	" 01NSWE\n"
# define DIRECTIONS	"NSWE"

# define K_ESC	65307
# define K_LT	65361
# define K_UP	65362
# define K_RT	65363
# define K_DN	65364
# define K_W	119
# define K_S	115
# define K_A	97
# define K_D	100

typedef enum e_error
{
	default_err,
	sys_err,
	init_err,
	arg_err,
	file_err,
}	t_error;

typedef enum e_texture
{
	north,
	south,
	east,
	west
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_data
{
	char	*name;
	char	**map;
	int		width;
	int		height;
	char	*texture[NB_TEXTURES];
	t_color	ceil;
	t_color	floor;
}	t_data;

typedef struct s_cam
{
	t_pos	cam_pos;
	t_pos	cam_dir;
	t_pos	cam_plane;
}	t_cam;

typedef struct s_img
{
	void	*img;
	char	*adrr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef	struct	s_win
{
	void		*ptr;
	t_img		img;
	t_pos		size;
	t_pos		half;
	double		ratio;
}				t_win;

typedef struct	s_game
{
	t_data	data;
	void	*mlx;
	t_win	win;
	t_cam	cam;
	int		exit_status;
}	t_game;

/* initialization init.c */
int		ft_init_game(t_game *game);

/* error management error.c*/
int		ft_error(t_error error_type, char *msg);
int		ft_error_exit(t_error error_type, char *msg, t_game *game);
/* free memory management free.c */
int		ft_free_tab(char **tab);
int		ft_free_game(t_game *game);
int		ft_free_data(t_data*data);

/* file parsing parser.c */
int		ft_read_file(t_game *game, char *arg);
/* parser utilities parser_utils.c */
int		ft_check_file(char *path);
char	**ft_tabdup_addline(char **tab, char *line, int size);
int		ft_check_inset(char *line, char *set);
int		ft_check_map(char **map, t_data *data);

#endif