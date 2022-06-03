/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:24:53 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/30 17:25:09 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ DEFINES ~~~                              */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_GAME_H
# define RENDER_GAME_H

/* ************************************************************************** */
/*                                                                            */
/*                              ~~~ PROTOTYPES ~~~                            */
/*                                                                            */
/* ************************************************************************** */

/*	render_game/ray_casting.c									*/
void	ray_casting(t_data *data);
void	throw_ray(t_data *data, int i, double angle);
void	render_walls(t_data *data, int i, double angle, double step);

/*	render_game/render_game.c									*/
void	render_game(t_data *data, t_config *config, t_win *win);
void	init_images(t_data *data, t_config *config);

/*	render_game/render_mini_map.c								*/
void	render_mini_map(t_data *data, t_config *config);
void	render_player(t_data *data);

/*	render_game/render_rect.c									*/
int		render_rect(t_data *data, t_img *render, t_rect rect);

#endif