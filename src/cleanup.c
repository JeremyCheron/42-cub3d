/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:13:40 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/19 11:15:08 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include "../includes/render.h"
#include "../includes/player.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	clear_game(t_game *game)
{
	if (game->mlx)
	{
		if (game->image_global)
			mlx_delete_image(game->mlx, game->image_global);
		if (game->texture_north)
			mlx_delete_texture(game->texture_north);
		if (game->texture_south)
			mlx_delete_texture(game->texture_south);
		if (game->texture_east)
			mlx_delete_texture(game->texture_east);
		if (game->texture_west)
			mlx_delete_texture(game->texture_west);
		mlx_terminate(game->mlx);
		free(game->config.east_texture);
		free(game->config.north_texture);
		free(game->config.south_texture);
		free(game->config.west_texture);
		free_map(game->map);
	}
}
