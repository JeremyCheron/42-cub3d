/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:13:40 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/21 07:29:22 by jcheron          ###   ########.fr       */
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

void	clear_config(t_config *config)
{
	if (config->north_texture)
		free(config->north_texture);
	if (config->south_texture)
		free(config->south_texture);
	if (config->east_texture)
		free(config->east_texture);
	if (config->west_texture)
		free(config->west_texture);
}

void	clear_game(t_game *game)
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
