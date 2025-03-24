/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:12:44 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 13:11:19 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include "../../includes/render.h"
#include "../../includes/player.h"

/**
 * @brief 🏃 Handles forward/backward movement
 * @param game Pointer to game structure
 * @param direction 1 for forward, -1 for backward
 */
static void	move_forward_backward(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	new_x = game->player.x + direction * cos_angle * PLAYER_SPEED;
	new_y = game->player.y + direction * sin_angle * PLAYER_SPEED;
	if (!is_wall(new_x, new_y, game))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/**
 * @brief 🚶 Handles strafe movement (left/right)
 * @param game Pointer to game structure
 * @param direction 1 for right, -1 for left
 */
static void	move_strafe(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	new_x = game->player.x - direction * sin_angle * PLAYER_SPEED;
	new_y = game->player.y + direction * cos_angle * PLAYER_SPEED;
	if (!is_wall(new_x, new_y, game))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/**
 * @brief 🔄 Handles player rotation
 * @param game Pointer to game structure
 * @param direction 1 for right, -1 for left
 */
static void	rotate_player(t_game *game, int direction)
{
	game->player.angle = fmod(game->player.angle + \
		direction * ANGLE_SPEED, 2 * PI);
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
}

/**
 * @brief 🎮 Main input handler for player movement
 * @param keydata Key press data from MLX
 * @param param Pointer to game structure (void* for MLX compatibility)
 */
void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W)
		move_forward_backward(game, 1);
	else if (keydata.key == MLX_KEY_S)
		move_forward_backward(game, -1);
	else if (keydata.key == MLX_KEY_A)
		move_strafe(game, -1);
	else if (keydata.key == MLX_KEY_D)
		move_strafe(game, 1);
	else if (keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_LEFT)
		rotate_player(game, -1);
	else if (keydata.key == MLX_KEY_E || keydata.key == MLX_KEY_RIGHT)
		rotate_player(game, 1);
}
