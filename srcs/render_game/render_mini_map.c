/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:49:41 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/06 17:50:26 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	render_mini_map(t_data *data, t_config *config)
{
	int		x;
	int		y;

	y = -1;
	while (++y < config->map_hgt && y < 15)
	{
		x = -1;
		while (config->map[y][++x] && x < 15)
		{
			if (config->map[y][x] == '1')
				render_rect(data, &data->mini_map, (t_rect){x * 8, y * 8, 8, 8, 0x01262E});
			else
				render_rect(data, &data->mini_map, (t_rect){x * 8, y * 8, 8, 8, 0xFFFFFF});
		}
	}
	render_player(data);
}

void	ini_camera_pos(t_data *data)
{
	int	x;
	int	y;

	y = data->player.pos.y - ((data->win.hgt / 64) / 2);
	x = data->player.pos.x - ((data->win.wdth / 64) / 2);
	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	if (y + data->win.hgt / 64 > data->config.map_hgt)
		y = data->config.map_hgt - (data->win.hgt / 64);
	if (x + data->win.wdth / 64 > data->config.map_wdth)
		x = data->config.map_wdth - (data->win.wdth / 64);
	data->camera.y = y;
	data->camera.x = x;
}

void	render_player(t_data *data)
{
	render_rect(data, &data->mini_map, (t_rect){data->player.pos.x, data->player.pos.y, 4, 4, 0xFFFF00});
}