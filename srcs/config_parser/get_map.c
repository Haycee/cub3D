/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:34:08 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/30 17:35:58 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The get_map.c file is where we :
	- we check that the map lines are found in the '.cub' file.
	- we check that the map does not contain any '\n'.
	- if that is the case, we put the map lines in our config struct,
	in a char** variable called map.
	- we also determine the map height here.
*/

#include "main.h"

static char	*get_first_line_of_map(t_config *config, int fd);
static char	*get_rest_of_map(t_config *config, int fd);

void	get_map(t_config *config, int fd)
{
	char	*map_first_line;
	char	*map_rest;
	char	*map_unidim;

	map_first_line = get_first_line_of_map(config, fd);
	map_rest = get_rest_of_map(config, fd);
	map_unidim = ft_strjoin(map_first_line, map_rest);
	free(map_rest);
	config->map = ft_split(map_unidim, '\n');
	free(map_unidim);
}

static char	*get_first_line_of_map(t_config *config, int fd)
{
	char	*map_start;

	map_start = NULL;
	while (1)
	{
		map_start = ft_get_next_line(fd);
		if (ft_strcmp(map_start, "\n") == failed)
			break;
		free(map_start);
	}
	config->map_hgt ++;
	if (!map_start)
		exit_with_error_message(map_err, missing);
	return (map_start);
}

static char	*get_rest_of_map(t_config *config, int fd)
{
	char	*line;
	char	*map_rest;
	int		i = 0;

	line = NULL;
	map_rest = NULL;
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr("\n", line[0]))
		{
			free(line);
			if (map_rest)
				free(map_rest);
			exit_with_error_message(map_err, new_line);
		}
		if (i == 0)
			map_rest = line;
		else
		{
			map_rest = ft_strjoin(map_rest, line);
			free(line);
		}
		i ++;
		config->map_hgt ++;
	}
	return (map_rest);
}