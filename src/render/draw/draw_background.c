/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 13:28:11 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

/**
 * @brief 🌅 Draws the sky part of the background
 * @param game Pointer to the game structure
 */
static void	draw_sky(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->image_global, x, y, \
			get_rgba(120, 190, 255, 255));
			x++;
		}
		y++;
	}
}

/**
 * @brief 🌱 Draws the ground part of the background
 * @param game Pointer to the game structure
 */
static void	draw_ground(t_game *game)
{
	int	x;
	int	y;

	y = WINDOW_HEIGHT / 2;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->image_global, x, y, get_rgba(63, 155, 11, 255));
			x++;
		}
		y++;
	}
}

/**
 * @brief 🌍 Draws the complete background (sky and ground)
 * @param game Pointer to the game structure
 */
void	draw_background(t_game *game)
{
	draw_sky(game);
	draw_ground(game);
}
