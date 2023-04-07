/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:08:09 by aquincho          #+#    #+#             */
/*   Updated: 2023/04/07 12:18:06 by aquincho         ###   ########.fr       */
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

# define TEX_SIZE	64
# define WIN_WIDTH	640
# define WIN_HEIGHT	480
# define ANGLE_FOV	60

typedef enum e_error
{
	default_err,
	sys_err,
	init_err,
	arg_err,
	rd_file_err,
	file_err
}	t_error;

typedef enum e_tex
{
	north,
	south,
	east,
	west,
	ceil_c,
	floor_c,
}	t_tex;

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
	t_pos	start_pos;
	t_pos	start_dir;
	int		data_read[7];
	bool	map_done;
}	t_data;

typedef struct s_cam
{
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
	int		height;
	double	move_speed;
	double	rot_speed;
}	t_cam;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	void	*ptr;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_win
{
	void	*ptr;
	t_pos	size;
	t_pos	half;
	double	ratio;
}	t_win;

typedef struct s_ray
{
	int		side;
	int		height;
	double	cam_x;
	t_pos	ray_pos;
	t_pos	dir;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	t_pos	side_dist;
	t_pos	delta_dist;
	double	wall_dist;
	t_pos	wall_start;
	t_pos	wall_end;
	t_tex	tex_type;
	double	tex_step;
	double	tex_wall_x;
	t_pos	tex_pos_int;
	t_pos	tex_pos;
}				t_ray;

typedef struct s_game
{
	t_data		data;
	void		*mlx;
	t_win		win;
	t_img		img;
	t_texture	texture[NB_TEXTURES];
	t_cam		cam;
	t_ray		ray;
	int			exit_status;
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
/* utilities utils.c */
void	ft_set_pos(t_pos *pos, double X, double Y);
int		ft_check_inset(char *line, char *set);
/* file .cub opening & reading read_file.c */
int		ft_read_file(t_game *game, char *arg);
int		ft_check_file(char *path);
/* file parsing parser.c */
int		ft_parser(int fd, t_data *data);
/* parser utilities parser_utils.c */
char	**ft_tabdup_addline(char **tab, char *line, int size);
int		ft_texture(char **texture, char *line, int *used);
int		ft_color(t_color *color, char *line, int *used);
void	ft_start_pos(t_data *data, int i, int j);
/* map parsing parser_map.c */
int		ft_map(t_data *data, int fd, char *line);
/* parser checking parser_check.c*/
int		ft_check_map(char **map, t_data *data);
/* game engine game.c */
int		ft_game(t_game game);
/* mlx and drawing init init_draw.c */
int		ft_init_mlx(t_game *game);
void	ft_init_draw(t_game *game);
/* make image draw.c */
int		ft_draw(t_game *game);
/* raycasting raycast.c*/
void	ft_raycast(t_game *game, int x);
/* engine utilities game_utils.c */
void	ft_pixel_put(t_img *img, t_pos pos, int color);
int		ft_rgb_to_int(int r, int g, int b);
int		ft_get_tex_color(t_texture *tex, t_pos *pos);
/* movement management move.c*/
int		ft_move_up_down(t_game *game, int direction);
int		ft_move_left_right(t_game *game, int direction);
int		ft_rotate_left(t_game *game);
int		ft_rotate_right(t_game *game);
/* free mlx management free_mlx.c*/
int		ft_kill_win(t_game *game);
void	ft_free_mlx(t_game *game);
#endif