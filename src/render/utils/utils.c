/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:12:44 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 14:47:06 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void init_player(t_player *player)
{
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->angle = PI * 1.5;
}

bool is_wall(double px, double py, t_game *game)
{
	const double buffer = 20.0;

	for (double angle = 0; angle < 2 * PI; angle += PI / 4)
	{
		double check_x = px + buffer * cos(angle);
		double check_y = py + buffer * sin(angle);

		int map_x = (int)(check_x / BLOCK_SIZE);
		int map_y = (int)(check_y / BLOCK_SIZE);

		if (map_x < 0 || map_y < 0 || !game->map[map_y] || !game->map[map_y][map_x])
			return true;

		if (game->map[map_y][map_x] == '1')
			return true;
	}

	return false;
}

void handle_input(mlx_key_data_t keydata, void *param)
{
	t_game *game;
	double new_x, new_y;

	game = (t_game *)param;
	double cos_angle = cos(game->player.angle);
	double sin_angle = sin(game->player.angle);

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
		new_x = game->player.x + cos_angle * PLAYER_SPEED;
		new_y = game->player.y + sin_angle * PLAYER_SPEED;
		if (!is_wall(new_x, new_y, game)) {
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
		new_x = game->player.x - cos_angle * PLAYER_SPEED;
		new_y = game->player.y - sin_angle * PLAYER_SPEED;
		if (!is_wall(new_x, new_y, game)) {
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
		new_x = game->player.x + sin_angle * PLAYER_SPEED;
		new_y = game->player.y - cos_angle * PLAYER_SPEED;
		if (!is_wall(new_x, new_y, game)) {
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
		new_x = game->player.x - sin_angle * PLAYER_SPEED;
		new_y = game->player.y + cos_angle * PLAYER_SPEED;
		if (!is_wall(new_x, new_y, game)) {
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_Q)
		game->player.angle = fmod(game->player.angle - ANGLE_SPEED, 2 * PI);
	else if (keydata.key == MLX_KEY_E)
		game->player.angle = fmod(game->player.angle + ANGLE_SPEED, 2 * PI);

	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
}