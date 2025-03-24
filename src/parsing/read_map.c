/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:41:45 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/24 12:25:46 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	handle_invalid_map(t_game *game, char *line)
{
	free(line);
	clear_config(&game->config);
	if (game->map)
		free_map(game->map);
	error_exit("ERROR: ", "Invalid map");
}

static void	handle_map_line(t_game *game, char *line,
	int *y, bool *map_started)
{
	*map_started = true;
	process_map_line(game, line, *y);
	(*y)++;
}

static void	process_line(t_game *game, char *line,
	int *y, bool *map_started)
{
	if (!(ft_isdigit(line[0])
			|| (ft_iswhitespace(line[0]) && ft_strlen(line) > 1))
		&& is_config_line(line, game))
		process_config_line(game, line);
	else if (line[0] == '\n' && *map_started)
		handle_invalid_map(game, line);
	else if (ft_isdigit(line[0])
		|| (ft_iswhitespace(line[0] && ft_strlen(line) > 1)))
		handle_map_line(game, line, y, map_started);
}

char	**read_map(
	const char *filename,
	t_game *game)
{
	int		fd;
	char	*line;
	int		y;
	bool	map_started;

	y = 0;
	map_started = false;
	game->map = NULL;
	check_file((char *)filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit((char *)filename, ERR_OPEN_FILE);
	line = get_next_line(fd);
	while (line)
	{
		process_line(game, line, &y, &map_started);
		free(line);
		line = get_next_line(fd);
	}
	if (!check_single_spawn(game))
		handle_invalid_map(game, line);
	return (free(line), close(fd), game->map);
}
