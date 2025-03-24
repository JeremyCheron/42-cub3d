/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/12 08:54:15 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub.h"

// Game initialization
// bool	init_game(t_game *game);

// Player initialization
void	init_player(t_player *player);

// Collision detection
bool	is_wall(double px, double py, t_game *game);
bool	check_collision_point(double check_x, double check_y, t_game *game);

// Movement handling
void	handle_input(mlx_key_data_t keydata, void *param);

#endif
