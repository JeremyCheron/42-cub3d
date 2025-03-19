/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/19 11:13:25 by edetoh           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit(argv[0], "Usage: ./cub3D <map.cub>");
	read_map(argv[1], &game);
	if (!init_game(&game))
	{
		ft_putendl_fd("Error\nFailed to initialize game", 2);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx);
	clear_game(&game);
	return (0);
}
