/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:23:09 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/03 14:36:21 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_wall(t_data *data, int i, double angle, double step);
static int	get_tex_color(t_texture *texture, t_coord *coord);

void	ray_casting(t_data *data)
{
	int		i;
	double	angle;

	i = -1;
	while (++i < (data->config.map_wdth * 64))
	{
		angle = data->player.dir.angle - data->player.fov / 2 + data->player.fov * i / ((double)data->config.map_wdth * 64);
		throw_ray(data, i, angle);
	}
	mlx_put_image_to_window(data->win.mlx, data->win.edge, data->walls.ptr, 512, 0);
}

void	throw_ray(t_data *data, int i, double angle)
{
	double	ray_x;
	double	ray_y;
	double	step;

	step = 0;
	while(step < 520)
	{
		ray_x = data->player.pos.x + step * cos(angle);
		ray_y = data->player.pos.y + step * sin(angle);
		if (data->config.map[(int)ray_y / 64][(int)ray_x / 64] == '1')
		{
			render_walls(data, i, angle, step);
			break;
		}
		pixel_put(&data->mini_map, ray_x, ray_y, 0xFFC0CB); // display rays on the mini_map
		step += 0.05;
	}
}

void	render_walls(t_data *data, int i, double angle, double step)
{
	float	column_hgt;

	column_hgt = (data->win.hgt / (step * cos(angle - data->player.dir.angle))) * 25;
	render_rect(data, &data->walls, (t_rect){data->win.wdth/2+i, 0, 1, data->win.hgt/2+column_hgt/2, data->config.ceiling_hex_code}); // draw ceiling
	// render_rect(data, &data->walls, (t_rect){data->win.wdth/2+i, data->win.hgt/2-column_hgt/2, 1, column_hgt, 0xFFFFFF}); // draw wall
	render_rect(data, &data->walls, (t_rect){data->win.wdth/2+i, data->win.hgt/2+column_hgt/2 - 1, 1, data->win.hgt - (data->win.hgt/2+column_hgt/2), data->config.floor_hex_code}); // draw floor
	draw_wall(data, i, angle, step);
}

static void	draw_wall(t_data *data, int i, double angle, double step)
{
	double	column_hgt;
	int		color;
	int		j;

	column_hgt = (data->win.hgt / (step * cos(angle - data->player.dir.angle))) * 25;

	double	ray_x = data->player.pos.x + step * cos(angle);
	double	ray_y = data->player.pos.y + step * sin(angle);
	
	double texture_x = (((int)ray_x + (int)ray_y) % 64);

	double	texture_y = 64;
	double	texture_step = 64.0 / column_hgt;

	j = 0;
	while (j++ < column_hgt)
	{
		texture_y -= texture_step;
		if (texture_y < 0)
			texture_y = 0;
		color = get_tex_color(&data->east_texture, &(t_coord){texture_x, texture_y});
		pixel_put(&data->walls, data->win.wdth/2+i, data->win.hgt/2+column_hgt/2 - 1 - j, color);
	}
}

static int	get_tex_color(t_texture *texture, t_coord *coord)
{
	if (coord->x >= 0 && coord->x < texture->wdth && coord->y >= 0 && coord->y < texture->hgt)
	{
		return (*(int*)(texture->ptr + (4 * texture->wdth * (int)coord->y) + (4 * (int)coord->x)));
	}
	printf("x : %f, y : %f\n", coord->x, coord->y);
	return (0xFFE436);
}













