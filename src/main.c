/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 13:11:40 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include "../includes/render.h"
#include "../includes/player.h"

/**
 * @brief 🎮 Configure les hooks pour les événements du jeu
 * @param game Pointeur vers la structure du jeu
 */
static void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
}

/**
 * @brief 🔍 Vérifie les arguments du programme
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguments
 * @return true si les arguments sont valides, false sinon
 */
static bool	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./cub3D <map.cub>", 2);
		return (false);
	}
	if (!ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_putendl_fd("Error\nMap file must end with .cub", 2);
		return (false);
	}
	return (true);
}

/**
 * @brief 🎯 Point d'entrée principal du programme
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguments
 * @return 0 en cas de succès, 1 en cas d'erreur
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv)) // a modifier (ajouter le !)
		return (1);
	if (!init_game(&game))
	{
		ft_putendl_fd("Error\nFailed to initialize game", 2);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
