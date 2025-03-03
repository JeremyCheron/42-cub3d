/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 13:28:26 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

/**
 * @brief 🎨 Converts RGB and alpha values to a single color integer
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @param a Alpha component (0-255)
 * @return Combined RGBA color value
 */
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief 🧹 Clears the entire game image with black color
 * @param game Pointer to the game structure
 */
void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->image_global, x, y, get_rgba(0, 0, 0, 255));
			x++;
		}
		y++;
	}
}

/**
 * @brief 📏 Clamps a value between a minimum and maximum
 * @param value Value to clamp
 * @param min Minimum allowed value
 * @param max Maximum allowed value
 * @return Clamped value
 */
double	ft_clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
