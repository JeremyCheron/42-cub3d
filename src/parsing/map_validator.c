/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:11:10 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/21 08:02:19 by jcheron          ###   ########.fr       */
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

bool	validate_map(t_game *game)
{
	char	**map_copy;

	map_copy = malloc(sizeof(char *) * (get_map_height(game) + 1));
	if (!map_copy)
		error_exit("ERROR: ", "Malloc failed");
	copy_map(map_copy, game);
	if (!check_flood_fill(map_copy, game)
		|| !check_remaining_zeroes(map_copy, game))
	{
		free_map(map_copy);
		return (false);
	}
	free_map(map_copy);
	return (true);
}
