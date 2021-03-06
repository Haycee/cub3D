/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:36:07 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/07 15:46:36 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The render_game.c file is where we :
	- initialize the mini_map image.
	- add pixels to the image that correspond to:
		- the map
		- the player position
		- the rays
	- put the mini_map imge to the window
*/

#include "main.h"

void	render_game(t_data *data, t_config *config, t_win *win)
{
	(void)config;
	(void)win;
	ray_casting(data);
	render_mini_map(data, config);
	mlx_put_image_to_window(win->mlx, win->edge, data->walls.ptr, 0, 0);
}