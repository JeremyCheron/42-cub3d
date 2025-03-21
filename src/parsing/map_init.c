/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 07:50:31 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/21 07:25:18 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	set_player_position(t_game *game, char c, int x, int y)
{
	game->player.x = x * BLOCK_SIZE + (BLOCK_SIZE / 2);
	game->player.y = y * BLOCK_SIZE + (BLOCK_SIZE / 2);
	if (c == 'N')
		game->player.angle = PI * 1.5;
	else if (c == 'S')
		game->player.angle = PI / 2;
	else if (c == 'E')
		game->player.angle = 0;
	else if (c == 'W')
		game->player.angle = PI;
	else
		return ;
}

void	process_map_line(t_game *game, char *line, int y)
{
	int		x;

	game->map = append_line_to_map(game->map, line);
	if (!game->map)
		return ;
	x = 0;
	while (line[x])
	{
		if (ft_strchr("NSEW", line[x]))
			set_player_position(game, line[x], x, y);
		x++;
	}
}

void	process_config_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_texture(&game->config.north_texture, line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_texture(&game->config.south_texture, line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_texture(&game->config.west_texture, line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_texture(&game->config.east_texture, line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line, game->config.floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line, game->config.ceiling_color);
}
