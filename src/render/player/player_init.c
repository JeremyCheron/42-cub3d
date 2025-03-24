/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/14 13:38:22 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include "../../includes/render.h"
#include "../../includes/player.h"

/**
 * @brief 🎮 Initialise la position et l'orientation du joueur
 * @param player Pointeur vers la structure du joueur
 */
void	print_game_infos(t_game *game)
{
	printf("\n===== Cub3D =====\n");
	printf("🪟 Window size: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
	printf("🧍 Player position: (%.2f, %.2f)\n", game->player.x, game->player.y);
	printf("👀 Player angle: %.2f\n", game->player.angle);
	printf("🏃 Player speed: %.2d\n", PLAYER_SPEED);
	printf("🤖 Player angle speed: %.2f\n\n", ANGLE_SPEED);
	printf("🗺️ N Texture path: %s\n", game->config.north_texture);
	printf("🗺️ S Texture path: %s\n", game->config.south_texture);
	printf("🗺️ W Texture path: %s\n", game->config.west_texture);
	printf("🗺️ E Texture path: %s\n", game->config.east_texture);
	printf("🔵 Celling color : %d, %d, %d\n", \
		game->config.ceiling_color[0], game->config.ceiling_color[1], \
		game->config.ceiling_color[2]);
	printf("🟢 Floor color : %d, %d, %d\n", \
		game->config.floor_color[0], game->config.floor_color[1], \
		game->config.floor_color[2]);
	printf("=================\n\n");
	return ;
}

/**
 * @brief 🎨 Charge les textures du jeu
 * @param game Pointeur vers la structure du jeu
 * @return true si le chargement réussit, false sinon
 */
static bool	load_game_textures(t_game *game)
{
	game->texture_north = mlx_load_png(game->config.north_texture);
	if (!game->texture_north)
		return (false);
	game->texture_south = mlx_load_png(game->config.south_texture);
	if (!game->texture_south)
		return (false);
	game->texture_east = mlx_load_png(game->config.east_texture);
	if (!game->texture_east)
		return (false);
	game->texture_west = mlx_load_png(game->config.west_texture);
	if (!game->texture_west)
		return (false);
	return (true);
}

/**
 * @brief 🎯 Initialise le jeu
 * @param game Pointeur vers la structure du jeu
 * @return true si l'initialisation réussit, false sinon
 */
bool	init_game(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (false);
	game->image_global = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->image_global)
	{
		mlx_terminate(game->mlx);
		return (false);
	}
	if (!game->map)
	{
		mlx_delete_image(game->mlx, game->image_global);
		mlx_terminate(game->mlx);
		return (false);
	}
	if (!load_game_textures(game))
	{
		mlx_delete_image(game->mlx, game->image_global);
		mlx_terminate(game->mlx);
		return (false);
	}
	print_game_infos(game);
	mlx_image_to_window(game->mlx, game->image_global, 0, 0);
	return (true);
}
