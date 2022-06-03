/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:52:27 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/30 17:52:56 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	render_rect(t_data *data, t_img *render, t_rect rect)
{
	int	i;
	int	j;

	if (data->win.edge == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.hgt)
	{
		j = rect.x;
		while (j < rect.x + rect.wdth)
		{
			pixel_put(render, j, i, rect.color);
			j ++;
		}
		i++;
	}
	return (0);
}
