/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:25:37 by edetoh            #+#    #+#             */
/*   Updated: 2024/12/27 16:21:24 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

// static int	can_move(t_game *game, int new_x, int new_y)
// {
// 	// char	next_pos;
// 	//
// 	// next_pos = game->map->grid[new_y][new_x];
// 	// if (next_pos == WALL)
// 	// 	return (0);
// 	// if (next_pos == EXIT && game->collected != game->map->collectibles)
// 	// 	return (0);
// 	(void)game;
// 	(void)new_x;
// 	(void)new_y;
// 	return (1);
// }

static void	update_player_position(t_game *game, float new_x, float new_y)
{
	// game->map->grid[game->player_y][game->player_x] = EMPTY;
	// game->map->grid[new_y][new_x] = PLAYER;
	game->player->instances[0].x = new_x * TILE_SIZE;
	game->player->instances[0].y = new_y * TILE_SIZE;
	printf("=============== MOVE PLAYER ===============\n")	;
	printf("Old x %f, New x %f\n", game->player_x, new_x);
	printf("Old y %f, New y %f\n", game->player_y, new_y);
	printf("===============            ===============\n")	;
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	rotate_player_x(t_game *game, float angle)
{
	if (angle < 0)
		game->player_angle += angle;
	else
		game->player_angle += angle;
	if (game->player_angle > 2 * PI)
			game->player_angle = 0;
	if (game->player_angle < 0)
			game->player_angle = 2 * PI;
	printf("=============== ROTATE PLAYER ===============\n")	;
	printf("Angle: %f\n", game->player_angle);
	printf("===============            ===============\n")	;
}

void	move_player(t_game *game, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	// if (!can_move(game, new_x, new_y))
	// 	return ;
	// {
	// 	ft_printf("Congratulations! You won in %d moves!\n", game->moves + 1);
	// 	mlx_close_window(game->mlx);
	// 	return ;
	// }
	update_player_position(game, new_x, new_y);
}
