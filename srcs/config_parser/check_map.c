/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:32:54 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/30 17:32:54 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The check_map.c file is where we :
	- check that the map contains only allowed characters (0,1,N,S,W, and E).
	- initialize the orientation and position of the player.
	- check that there is (only) one player on the map.
- check that the map is closed, i.e. surrounded by walls ('1' characters).
*/

#include "main.h"

static int	player_init(t_config *config, t_player *player, int x, int y);
static int	is_closed(t_config *config, int x, int y);
static int	check_vertical_lines(t_config *config, int x, int y);
static int	check_horizontal_lines(t_config *config, int y);

void	check_map(t_config *config, t_player *player)
{
	int	y;
	int	x;

	y = -1;
	while (++y < config->map_hgt)
	{
		x = -1;
		while (config->map[y][++x])
		{
			if (!ft_strchr("01NSEW", config->map[y][x]))
				exit_with_error_message(map_err, invalid);
			if (ft_strchr("NSEW", config->map[y][x]))
				if (player_init(config, player, x, y) == failed)
				exit_with_error_message(map_err, n_player);
			if (config->map[y][x] != '1')
				if (is_closed(config, x, y) == NO)
					exit_with_error_message(map_err, walls);
			if (x + 1 > config->map_wdth)
				config->map_wdth = x + 1;
		}
	}
	if (!config->player_orientation)
		exit_with_error_message(map_err, n_player);
}

static int	player_init(t_config *config, t_player *player, int x, int y)
{
	if (config->player_orientation != 0)
		return (failed);
	config->player_orientation = config->map[y][x];
	player->pos.x = x * 64 + 27;
	player->pos.y = y * 64 + 27;
	return (success);
}

static int	is_closed(t_config *config, int x, int y)
{
	if (check_vertical_lines(config, x, y) == failed
		|| check_horizontal_lines(config, y) == failed)
		return (NO);
	return (YES);
}

static int	check_vertical_lines(t_config *config, int x, int y)
{
	int	wall_found;
	int	i;

	if (y == config->map_hgt || y == 0)
		return (failed);
	wall_found = 0;
	i = y;
	while (i < config->map_hgt && i != 0)
	{
		if (wall_found == 0)
			i++;
		else
			i--;
		if (!((int)ft_strlen(config->map[i]) - 1 >= x))
			return (failed);
		if (config->map[i][x] == '1')
			wall_found++;
		if (wall_found == 2)
			return (success);
	}
	return (failed);
}

static int	check_horizontal_lines(t_config *config, int y)
{
	int	line_size;

	line_size = (int)ft_strlen(config->map[y]) - 1;
	if (config->map[y][line_size] != '1' || config->map[y][0] != '1')
		return (failed);
	return (success);
}
