/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:59:09 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/21 10:12:13 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

bool	check_flood_fill(char **map_copy, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < get_map_height(game))
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == '0' || map_copy[i][j] == 'N'
				|| map_copy[i][j] == 'S' || map_copy[i][j] == 'W'
				|| map_copy[i][j] == 'E')
			{
				if (!flood_fill(map_copy, j, i, game))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_remaining_zeroes(char **map_copy, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < get_map_height(game))
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == '0')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
