/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:32:25 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/30 17:35:58 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The init_player.c file is where we initialize the direction vector.
	The x and y coordinates and the angle depend on player_orientation.
	player_orientation is found in config struct but is passed
	as a char argument to the function init_player.
*/

#include "main.h"

void	init_player(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->dir.angle = (3 * M_PI)/2;
	}
	else if (c == 'S')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->dir.angle = M_PI/2;
	}
	else if (c == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->dir.angle = M_PI;
	}
	else if (c == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->dir.angle = 2 * M_PI;
	}
	player->fov = M_PI / 3;
	player->delta_x = cos(player->dir.angle) * 5;
	player->delta_y = sin(player->dir.angle) * 5;
}