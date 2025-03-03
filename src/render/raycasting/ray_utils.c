/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 13:17:05 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"
#include "../../../includes/render.h"

/**
 * @brief 📏 Calculates the distance between two points
 * @param x X component of the vector
 * @param y Y component of the vector
 * @return Euclidean distance
 */
double	distance(float x, float y)
{
	return (sqrtf(x * x + y * y));
}

/**
 * @brief 🎯 Checks if a point intersects with a wall
 * @param px X coordinate to check
 * @param py Y coordinate to check
 * @param game Pointer to the game structure
 * @return true if point intersects with wall, false otherwise
 */
bool	touch(double px, double py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK_SIZE);
	y = (int)(py / BLOCK_SIZE);
	if (x < 0 || y < 0 || !game->map[y] || !game->map[y][x])
		return (true);
	return (game->map[y][x] == '1');
}

/**
 * @brief 📐 Calculates the fixed (perpendicular) distance to a wall
 * @param start Starting point coordinates
 * @param end Ending point coordinates
 * @param game Pointer to game structure
 * @return Fixed distance to wall
 */
double	fixed_dist(t_point start, t_point end, t_game *game)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	fix_dist;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
