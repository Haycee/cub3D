/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:33:26 by llethuil          #+#    #+#             */
/*   Updated: 2022/06/01 10:04:47 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The config_parser.c file is where we :
	- open the '.cub' file that has been selected by the user,
	- initialize our 'config' structure with the data stored in the '.cub' file,
	- close the '.cub' file,
	- parse the data we have extracted from the '.cub' file.
*/

#include "main.h"

void	config_parser(int ac, char **av, t_config *config, t_player *player)
{
	int	fd;

	fd = open_file(ac, av);
	get_config_lines(config, fd);
	get_map(config, fd);
	close_file(fd);
	replace_spaces_in_map(config);
	check_map(config, player);
	parse_config_lines(config);
	check_texture_paths(config);
	get_rgb_code_int_tabs(config);
	convert_rgb_codes_to_hex(config);
}
