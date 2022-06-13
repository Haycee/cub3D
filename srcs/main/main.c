/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:32:40 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/12 16:12:01 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The main.c file is where we :
	- initialize our data structure,
	- get the specifications,
*/

// segfault quand trop proche d'un mur + change orientation du joueur
// !! map_wdth !! toutes les lignes ne font pas la même taille

#include "main.h"

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	config_parser(ac, av, &data.config, &data.player);
	window_manager(&data);
	init_player(&data, &data.player, data.config.player_orientation);
	init_images(&data, &data.config);
	render_game(&data, &data.config, &data.win);
	mlx_hook(data.win.edge, 2, 0, key_press, &data);
	mlx_loop(data.win.mlx);
	exit (0);
}

void	init_images(t_data *data, t_config *config)
{
	(void)config;
	// data->mini_map.ptr = mlx_new_image(data->win.mlx, 120, 120);
	// data->mini_map.addr = mlx_get_data_addr(data->mini_map.ptr, &data->mini_map.bpp, &data->mini_map.line_len, &data->mini_map.endian);
	data->walls.ptr = mlx_new_image(data->win.mlx, data->win.wdth, data->win.hgt);
	data->walls.addr = mlx_get_data_addr(data->walls.ptr, &data->walls.bpp, &data->walls.line_len, &data->walls.endian);
	data->east_texture.tex = mlx_xpm_file_to_image(data->win.mlx, data->config.ea_texture_path, &data->east_texture.wdth, &data->east_texture.hgt);
	data->east_texture.ptr = mlx_get_data_addr(data->east_texture.tex, &data->east_texture.bpp, &data->east_texture.line_len, &data->east_texture.endian);
	data->north_texture.tex = mlx_xpm_file_to_image(data->win.mlx, data->config.no_texture_path, &data->north_texture.wdth, &data->north_texture.hgt);
	data->north_texture.ptr = mlx_get_data_addr(data->north_texture.tex, &data->north_texture.bpp, &data->north_texture.line_len, &data->north_texture.endian);
	data->south_texture.tex = mlx_xpm_file_to_image(data->win.mlx, data->config.so_texture_path, &data->south_texture.wdth, &data->south_texture.hgt);
	data->south_texture.ptr = mlx_get_data_addr(data->south_texture.tex, &data->south_texture.bpp, &data->south_texture.line_len, &data->south_texture.endian);
	data->west_texture.tex = mlx_xpm_file_to_image(data->win.mlx, data->config.we_texture_path, &data->west_texture.wdth, &data->west_texture.hgt);
	data->west_texture.ptr = mlx_get_data_addr(data->west_texture.tex, &data->west_texture.bpp, &data->west_texture.line_len, &data->west_texture.endian);
}