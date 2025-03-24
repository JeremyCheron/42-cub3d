/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:12:44 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 13:28:45 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include "../../includes/render.h"
#include "../../includes/player.h"

/**
 * @brief 🎯 Checks if a specific point collides with map boundaries or walls
 * @param check_x X coordinate to check
 * @param check_y Y coordinate to check
 * @param game Pointer to game structure
 * @return true if collision detected, false otherwise
 */
bool	check_collision_point(double check_x, double check_y, t_game *game)
{
	int		map_x;
	int		map_y;
	size_t	line_len;

	map_x = (int)(check_x / BLOCK_SIZE);
	map_y = (int)(check_y / BLOCK_SIZE);
	if (map_x < 0 || map_y < 0)
		return (true);
	if (!game->map[map_y])
		return (true);
	line_len = ft_strlen(game->map[map_y]);
	if ((size_t)map_x >= line_len)
		return (true);
	return (game->map[map_y][map_x] == '1');
}

/**
 * @brief 🛡️ Checks if a point collides with walls
 * @param px X coordinate to check
 * @param py Y coordinate to check
 * @param game Pointer to game structure
 * @return true if collision detected, false otherwise
 */
bool	is_wall(double px, double py, t_game *game)
{
	const double	buffer = 10.0;
	double			angle;
	double			check_x;
	double			check_y;

	if (px < 0 || py < 0)
		return (true);
	angle = 0;
	while (angle < 2 * PI)
	{
		check_x = px + buffer * cos(angle);
		check_y = py + buffer * sin(angle);
		if (check_collision_point(check_x, check_y, game))
			return (true);
		angle += PI / 4;
	}
	return (false);
}
