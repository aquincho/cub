/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:08:09 by aquincho          #+#    #+#             */
/*   Updated: 2023/02/27 11:58:38 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef enum e_error
{
	default_err,
	sys_err,
	init_err,
	arg_err,
	file_err,
}	t_error;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_tex
{
	char	*path;
}	t_tex;

typedef struct s_data
{
	char	*name;
	char	**map;
	int		width;
	int		height;
	char	*n_wall;
	char	*s_wall;
	char	*e_wall;
	char	*w_wall;
	t_color	ceil;
	t_color	floor;
}	t_data;

typedef struct	s_game
{
	t_data	data;
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

#endif