/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 15:41:17 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include "../../includes/render.h"

/**
 * @brief 🎯 Casts rays for the entire screen width
 * @param game Pointer to game structure
 */
static void	cast_rays(t_game *game)
{
	double	fraction;
	double	start_x;
	int		i;
	t_ray	ray;

	fraction = PI / 3 / WINDOW_WIDTH;
	start_x = game->player.angle - PI / 6;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		init_ray(&ray, start_x, game);
		calculate_step(&ray);
		detect_wall(&ray, game);
		draw_wall_line(&ray, game, i, start_x);
		start_x += fraction;
		i++;
	}
}

/**
 * @brief 🔄 Main rendering loop function
 * @param param Pointer to game structure (cast from void*)
 */
void	draw_loop(void *param)
{
	static double	x;
	static double	y;
	static double	angle;
	t_game			*game;

	game = (t_game *)param;
	if (x != game->player.x || y != game->player.y || \
		angle != game->player.angle)
	{
		clear_image(game);
		draw_background(game);
		cast_rays(game);
		mlx_image_to_window(game->mlx, game->image_global, 0, 0);
		x = game->player.x;
		y = game->player.y;
		angle = game->player.angle;
	}
}
