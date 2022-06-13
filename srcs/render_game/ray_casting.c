/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:23:09 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/13 11:35:34 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			draw_wall(t_data *data, int i, double column_hgt);
static int			get_tex_color(t_texture *texture, t_coord *coord);
static t_ray		try_ray(t_data *data, int i);
static t_texture	get_texture(t_data *data, int i);

void	ray_casting(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->win.wdth)
	{
		data->ray.angle = data->player.dir.angle - data->player.fov / 2 + data->player.fov * i / ((double)data->win.wdth);
		throw_ray(data, i);
	}
	mlx_put_image_to_window(data->win.mlx, data->win.edge, data->walls.ptr, 0, 0);
}

void	throw_ray(t_data *data, int i)
{
	data->ray.step = 0;
	while(data->ray.step < 300000)
	{
		data->ray.x = data->player.pos.x + data->ray.step * cos(data->ray.angle);
		data->ray.y = data->player.pos.y + data->ray.step * sin(data->ray.angle);
		if (data->config.map[(int)data->ray.y / 64][(int)data->ray.x / 64] == '1')
		{
			render_walls(data, i);
			break;
		}
		// pixel_put(&data->mini_map, ray_x, ray_y, 0xFFC0CB); // display rays on the mini_map
		data->ray.step += 0.05;
	}
}

void	render_walls(t_data *data, int i)
{
	double	column_hgt;


	column_hgt = (data->win.hgt / (data->ray.step * cos(data->ray.angle - data->player.dir.angle))) * 25;
	
	// render ceiling
	render_rect(data, &data->walls, (t_rect){i, 0, 1, data->win.hgt/2+column_hgt/2, data->config.ceiling_hex_code});
	// render floor
	render_rect(data, &data->walls, (t_rect){i, data->win.hgt/2+column_hgt/2 + 1, 1, data->win.hgt - (data->win.hgt/2+column_hgt/2), data->config.floor_hex_code});
	// render walls
	draw_wall(data, i, column_hgt);
}

static void	draw_wall(t_data *data, int i, double column_hgt)
{
	t_texture	texture;
	int			color;
	int			j;
	
	double hit_x = (((int)data->ray.x + (int)data->ray.y) % 64);
	double	hit_y = 64;
	double	texture_step = 64.0 / column_hgt;

	texture = get_texture(data, i);
	j = 0;
	while (j++ < column_hgt)
	{
		hit_y -= texture_step;
		if (hit_y < 0)
			hit_y = 0;
		// color = get_tex_color(&data->north_texture, &(t_coord){hit_x, hit_y});
		color = get_tex_color(&texture, &(t_coord){hit_x, hit_y});
		pixel_put(&data->walls, i, data->win.hgt/2+column_hgt/2 - j, color);
	}
}

static t_texture	get_texture(t_data *data, int i)
{
	t_ray	ray_test;
	int		is_x;

	is_x = 0;

	ray_test = try_ray(data, i);
	if (ray_test.y + 0.1 >= data->ray.y && ray_test.y - 0.1 <= data->ray.y)
		is_x = 1;
	
	// printf("ray_test.y = %f		data->ray.y = %f\n", ray_test.y, data->ray.y);
	// printf("is_x = %d\n", is_x);

	if (data->player.orientation == 'N')
	{
		if (is_x == 1)
		{
			return (data->south_texture);
		}
		else
		{
			// if (data->player.dir.angle > data->ray.angle)
			if (data->player.pos.x > data->ray.x)
				return (data->east_texture);
			else
				return (data->west_texture);

			printf("player angle : %f		ray angle : %f\n", data->player.dir.angle, data->ray.angle);
		}
	}
	
	
	return (data->north_texture);
}



static t_ray	try_ray(t_data *data, int i)
{
	t_ray	ray;

	ray.step = 0;
	ray.angle = data->player.dir.angle - data->player.fov / 2 + data->player.fov * (i + 1) / ((double)data->win.wdth);
	while(ray.step < 300000)
	{
		ray.x = data->player.pos.x + ray.step * cos(ray.angle);
		ray.y = data->player.pos.y + ray.step * sin(ray.angle);
		if (data->config.map[(int)ray.y / 64][(int)ray.x / 64] == '1')
			return (ray);
		ray.step += 0.05;
	}
	return (ray);
}












static int	get_tex_color(t_texture *texture, t_coord *coord)
{
	if (coord->x >= 0 && coord->x < texture->wdth && coord->y >= 0 && coord->y < texture->hgt)
	{
		return (*(int*)(texture->ptr + (4 * texture->wdth * (int)coord->y) + (4 * (int)coord->x)));
	}
	return (0xFFE436);
}













