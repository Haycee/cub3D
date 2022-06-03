/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:49:41 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/01 10:11:52 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	render_mini_map(t_data *data, t_config *config)
{
	int		x;
	int		y;

	render_rect(data, &data->mini_map, (t_rect){0, 0, config->map_wdth * 64, config->map_hgt * 64, 0x808080});
	y = -1;
	while (++y < config->map_hgt)
	{
		x = -1;
		while (config->map[y][++x])
		{
			if (config->map[y][x] == '1')
				render_rect(data, &data->mini_map, (t_rect){x * 64, y * 64, 63, 63, 0xFFFFFF});
			else
				render_rect(data, &data->mini_map, (t_rect){x * 64, y * 64, 63, 63, 0x000000});
		}
	}
	render_player(data);
}

void	render_player(t_data *data)
{
	render_rect(data, &data->mini_map, (t_rect){data->player.pos.x, data->player.pos.y, 10, 10, 0xFFFF00});
}