/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:22:50 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/12 15:04:55 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The header.h file is where we :
	- include pre-existing header files,
	- define our macros and enums,
	- declare typedefs for our structures.
*/

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ DEFINES ~~~                              */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ ENUMS ~~~                                */
/*                                                                            */
/* ************************************************************************** */

enum e_result {
	success,
	failed
};

enum e_found {
	found,
	not_found
};

enum e_err_type {
	open_err,
	config_err,
	map_err
};

enum e_err_no {
	n_arg,
	extension,
	dir,
	fail,
	missing,
	invalid,
	new_line,
	n_player,
	walls
};

enum e_check {
	YES,
	NO
};

enum e_key {
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	ESC = 53,
	left_arrow = 123,
	right_arrow = 124
};

/* ************************************************************************** */
/*                                                                            */
/*                              ~~~ PROTOTYPES ~~~                            */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_config
{
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	char	*floor_rgb_str;
	char	*ceiling_rgb_str;
	int		*floor_rgb_int_tab;
	int		*ceiling_rgb_int_tab;
	int		floor_hex_code;
	int		ceiling_hex_code;
	char	**map;
	int		map_hgt;
	int		map_wdth;
	char	player_orientation;
}	t_config;

typedef struct s_win
{
	void	*mlx;
	void	*edge;
	void	*img_ptr;
	int		wdth;
	int		hgt;
	int		x;
	int		y;
}	t_win;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_texture
{
	char	*path;
	void	*tex;
	int		wdth;
	int		hgt;
	void	*ptr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_rect
{
	int	x;
	int	y;
	int	wdth;
	int	hgt;
	int	color;
}	t_rect;

typedef struct s_vector
{
	double	x;
	double	y;
	double	angle;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	double		delta_x;
	double		delta_y;
	double		fov;
	char		orientation;
}	t_player;

typedef struct s_ray
{
	double		angle;
	double		x;
	double		y;
	double		step;
}	t_ray;

typedef struct s_data
{
	t_config	config;
	t_win		win;
	t_player	player;
	t_ray		ray;
	t_img		mini_map;
	t_img		walls;
	t_texture	east_texture;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	west_texture;
	t_coord		camera;
}	t_data;

#endif
