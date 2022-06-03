/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_spaces_in_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:33:36 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/30 17:35:58 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
	The replace_spaces_in_map.c file is where we :
	- replace any space character found in the map by a '1'.
*/

#include "main.h"

void	replace_spaces_in_map(t_config *config)
{
	int	i;

	i = 0;
	while(config->map[i])
	{
		replace_spaces_in_str(config->map[i], '1');
		i ++;
	}
}
