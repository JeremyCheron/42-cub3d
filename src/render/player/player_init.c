/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/13 11:10:23 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include "../../includes/render.h"
#include "../../includes/player.h"

/**
 * @brief 🎮 Initialise la position et l'orientation du joueur
 * @param player Pointeur vers la structure du joueur
 */
void	init_player(t_player *player)
{
	player->angle = PI * 1.5;
}

/**
 * @brief 🗺️ Crée une carte de test
 * @return Tableau de chaînes représentant la carte
 */
// static char	**create_test_map(void)
// {
// 	char	**map;

// 	map = malloc(sizeof(char *) * 11);
// 	if (!map)
// 		return (NULL);
// 	map[0] = ft_strdup("1111111111111111");
// 	map[1] = ft_strdup("1000000000000001");
// 	map[2] = ft_strdup("1000000000000001");
// 	map[3] = ft_strdup("1000000000000001");
// 	map[4] = ft_strdup("1000010000000001");
// 	map[5] = ft_strdup("1000000000000001");
// 	map[6] = ft_strdup("1000000000000001");
// 	map[7] = ft_strdup("1000000001100001");
// 	map[8] = ft_strdup("1000000000100001");
// 	map[9] = ft_strdup("1111111111111111");
// 	map[10] = NULL;
// 	return (map);
// }

/**
 * @brief 🎨 Charge les textures du jeu
 * @param game Pointeur vers la structure du jeu
 * @return true si le chargement réussit, false sinon
 */
static bool	load_game_textures(t_game *game)
{
	game->texture_north = mlx_load_png("src/render/assets/wolftextures1.png");
	if (!game->texture_north)
		return (false);
	game->texture_south = mlx_load_png("src/render/assets/wolftextures2.png");
	if (!game->texture_south)
		return (false);
	game->texture_east = mlx_load_png("src/render/assets/wolftextures3.png");
	if (!game->texture_east)
		return (false);
	game->texture_west = mlx_load_png("src/render/assets/wolftextures4.png");
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
	// game->map = create_test_map();
	if (!game->map)
	{
		mlx_delete_image(game->mlx, game->image_global);
		mlx_terminate(game->mlx);
		return (false);
	}
	init_player(&game->player);
	if (!load_game_textures(game))
	{
		mlx_delete_image(game->mlx, game->image_global);
		mlx_terminate(game->mlx);
		return (false);
	}
	mlx_image_to_window(game->mlx, game->image_global, 0, 0);
	return (true);
}
