/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:45:41 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/20 17:22:51 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	main(int argc, char **argv)
{

	t_game	game;

	(void)argc;
	(void)argv;
	init_game(&game);
	draw_square(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 10, get_rgba(255, 0, 0, 255), &game);
	mlx_key_hook(game.mlx, handle_input, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	// draw_loop(&game);
	mlx_loop(game.mlx);
	return (0);
}