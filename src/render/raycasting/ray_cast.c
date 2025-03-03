/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
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
 * @brief 🎯 Initializes ray casting parameters
 * @param ray Pointer to ray parameters structure
 * @param fx Ray angle
 * @param game Pointer to game structure
 */
void	init_ray(t_ray *ray, double fx, t_game *game)
{
	ray->x = game->player.x;
	ray->y = game->player.y;
	ray->cos_angle = cos(fx);
	ray->sin_angle = sin(fx);
	if (ray->cos_angle == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->cos_angle);
	if (ray->sin_angle == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->sin_angle);
	ray->map_x = (int)(ray->x / BLOCK_SIZE);
	ray->map_y = (int)(ray->y / BLOCK_SIZE);
}

/**
 * @brief 🏃 Performs DDA step calculation
 * @param ray Pointer to ray parameters structure
 */
void	calculate_step(t_ray *ray)
{
	if (ray->cos_angle < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->x - ray->map_x * BLOCK_SIZE) \
		* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1.0) * BLOCK_SIZE - ray->x) * \
			ray->delta_dist_x;
	}
	if (ray->sin_angle < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->y - ray->map_y * BLOCK_SIZE) \
		* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1.0) * BLOCK_SIZE - ray->y) * \
			ray->delta_dist_y;
	}
}

/**
 * @brief 🔍 Performs DDA wall detection
 * @param ray Pointer to ray parameters structure
 * @param game Pointer to game structure
 */
void	detect_wall(t_ray *ray, t_game *game)
{
	ray->hit = false;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x * BLOCK_SIZE;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y * BLOCK_SIZE;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || !game->map[ray->map_y] || \
			!game->map[ray->map_y][ray->map_x])
			break ;
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}
}

/**
 * @brief 🎨 Draws a vertical line for the wall
 * @param ray Pointer to ray parameters structure
 * @param game Pointer to game structure
 * @param i Column index
 * @param fx Ray angle
 */
void	draw_wall_line(t_ray *ray, t_game *game, int i, double fx)
{
	t_wall	wall;

	calculate_wall_params(ray, game, fx, &wall);
	draw_textured_line(game, &wall, i);
}
