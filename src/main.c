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


static void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
}


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
