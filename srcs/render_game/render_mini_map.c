/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:49:41 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/10 09:49:24 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	render_wall(t_data *data, int x, int y);

void	render_mini_map(t_data *data, t_config *config)
{
	int		x;
	int		y;

	y = -1;
	while (++y < config->map_hgt) // Ajouter sécurité (taille max de la fenetre)
	{
		x = -1;
		while (++x < (int)ft_strlen(config->map[y]))
		{
			if (config->map[y][x] != '1')
				render_rect(data, &data->walls, (t_rect){(x * 7) + 10, (y * 7) + 10, 2, 2, 0xFFFFFF});
			else
				render_wall(data, x, y);
				// render_rect(data, &data->walls, (t_rect){(x * 7) + 10, (y * 7) + 10, 2, 2, 0x000000});
		}
	}
	render_player(data);
}

int	render_wall(t_data *data, int x, int y)
{
	int	check;

	check = 0;
	if (x > 0 && data->config.map[y][x - 1] != '1')
		check = 1;
	if (x < (int)ft_strlen(data->config.map[y]) && data->config.map[y][x + 1] != '1')
		if (data->config.map[y][x + 1] != 0)
			check = 1;
	if (y > 0 && (int)ft_strlen(data->config.map[y - 1]) >= x)
		if (data->config.map[y - 1][x] != '1')
			check = 1;
	if (y < data->config.map_hgt && ft_strlen(data->config.map[y + 1]) >= ft_strlen(data->config.map[y]))
		if (data->config.map[y + 1][x] != '1')
			check = 1;

	if (check == 1)
		render_rect(data, &data->walls, (t_rect){(x * 7) + 10, (y * 7) + 10, 2, 2, 0x000000});
	return (check);
}

void	render_player(t_data *data)
{
	double	x;
	double	y;

	x = ((data->player.pos.x / 64) * 7) + 8;
	// if (x > ((data->config.map_wdth - 2) * 7) + 12)
	// 	x = ((data->config.map_wdth - 2) * 7) + 10;
	// if (x < 17)
	// 	x = 19;
	y = ((data->player.pos.y / 64) * 7) + 8;
	// if (y > ((data->config.map_hgt - 2) * 7) + 12)
	// 	y = ((data->config.map_hgt - 2) * 7) + 10;
	// if (y < 17)
	// 	y = 19;
	render_rect(data, &data->walls, (t_rect){x, y, 2, 2, 0xFFFF00});
}