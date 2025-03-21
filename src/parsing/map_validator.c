/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:11:10 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/21 07:23:41 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	get_map_height(t_game *game)
{
	int	height;

	height = 0;
	while (game->map[height])
		height++;
	return (height);
}

void	copy_map(char **dest, t_game *game)
{
	int	i;

	i = 0;
	while (i < get_map_height(game))
	{
		printf("game->map[%d]: %s\n", i, game->map[i]);
		dest[i] = ft_strdup(game->map[i]);
		printf("dest[%d]: %s\n", i, dest[i]);
		if (!dest[i])
			error_exit("ERROR: ", "Malloc failed");
		i++;
	}
	dest[i] = NULL;
}

int	flood_fill(char **map, int x, int y, t_game *game)
{
	if (y < 0 || y >= get_map_height(game)
		|| x < 0 || x >= (int)ft_strlen(map[y])
		|| map[y][x] == '1' || map[y][x] == 'F')
		return (1);
	if (y == 0 || y == get_map_height(game) - 1
		|| x == 0 || x == (int)ft_strlen(map[y]) - 1)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	map[y][x] = 'F';
	printf("x: %d, y: %d --- %c\n", x, y, map[y][x]);
	if (!flood_fill(map, x + 1, y, game)
		|| !flood_fill(map, x - 1, y, game)
		|| !flood_fill(map, x, y + 1, game)
		|| !flood_fill(map, x, y - 1, game))
		return (0);
	return (1);
}

bool	validate_map(t_game *game)
{
	char	**map_copy;
	int		i;
	int		j;

	map_copy = malloc(sizeof(char *) * (get_map_height(game) + 1));
	if (!map_copy)
		error_exit("ERROR: ", "Malloc failed");
	copy_map(map_copy, game);
	i = 0;
	while (i < get_map_height(game))
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == '0' || map_copy[i][j] == 'N')
			{
				if (!flood_fill(map_copy, j, i, game))
				{
					free_map(map_copy);
					return (false);
				}
			}
			j++;
		}
		printf("map_copy[%d]: %s\n", i, map_copy[i]);
		i++;
	}
	i = 0;
	while (i < get_map_height(game))
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == '0')
			{
				free_map(map_copy);
				return (false);
			}
			j++;
		}
		i++;
	}
	free_map(map_copy);
	return (true);
}
