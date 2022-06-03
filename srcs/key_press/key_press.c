/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:32:34 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/02 19:10:58 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The key_press.c file is where we :
	- make the player moving depending on the key pressed by the user.
	- render the mini_map, updating the new position of the player.
*/

#include "main.h"

static int	check_collision(t_data *data, int key);
static int	throw_collision_ray(t_data *data, double angle);

int	key_press(int key, t_data *data)
{
	if (key == W)
		move_up(data);;
	if (key == S)
		move_down(data);
	if (key == ESC)
		close_window(data);
	if (key == left_arrow)
		turn_left(data);
	if (key == right_arrow)
		turn_right(data);
	render_game(data, &data->config, &data->win);
	return (0);
}

void	turn_left(t_data *data)
{
	data->player.dir.angle -= M_PI / 90;
	if (data->player.dir.angle < 0)
		data->player.dir.angle += 2 * M_PI;
	data->player.delta_x = cos(data->player.dir.angle) * 5;
	data->player.delta_y = sin(data->player.dir.angle) * 5;
}

void	turn_right(t_data *data)
{
	data->player.dir.angle += M_PI / 90;
	if (data->player.dir.angle > 2 * M_PI)
		data->player.dir.angle -= 2 * M_PI;
	data->player.delta_x = cos(data->player.dir.angle) * 5;
	data->player.delta_y = sin(data->player.dir.angle) * 5;
}

void	move_up(t_data *data)
{
	if (check_collision(data, W) == NO)
	{
		data->player.pos.y += data->player.delta_y;
		data->player.pos.x += data->player.delta_x;
	}
}

void	move_down(t_data *data)
{
	if (check_collision(data, S) == NO)
	{
		data->player.pos.x -= data->player.delta_x;
		data->player.pos.y -= data->player.delta_y;
	}
}

static int	check_collision(t_data *data, int key)
{
	int		i;
	double	angle;
	double	collision_fov;

	collision_fov = M_PI/6;

	i = 0;
	while (i < (data->config.map_wdth * 64))
	{
		angle = data->player.dir.angle - collision_fov / 2 + collision_fov * i / ((double)data->config.map_wdth * 64);
		if (key == S)
			angle += M_PI;
		if (throw_collision_ray(data, angle) == YES)
			return (YES);
		i += (data->config.map_wdth * 64) - 1;
	}
	// i =(data->config.map_wdth * 64) - 1;
	// angle = data->player.dir.angle - collision_fov / 2 + collision_fov * i / ((double)data->config.map_wdth * 64);
	// if (key == S)
	// 	angle += M_PI;
	// if (throw_collision_ray(data, angle) == YES)
	// 	return (YES);
	// mlx_put_image_to_window(data->win.mlx, data->win.edge, data->mini_map.ptr, 0, 0);
	return (NO);
}

static int	throw_collision_ray(t_data *data, double angle)
{
	double	ray_x;
	double	ray_y;
	double	step;

	step = 0;
	while(step < 25)
	{
		ray_x = data->player.pos.x + step * cos(angle);
		ray_y = data->player.pos.y + step * sin(angle);
		if (data->config.map[(int)ray_y / 64][(int)ray_x / 64] == '1')
			return (YES);
		pixel_put(&data->mini_map, ray_x, ray_y, 0xC70039); // display rays on the mini_map
		step += 0.05;
	}
	return (NO);
}