/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:41:45 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/13 08:44:17 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

// static bool	_is_cub_file(
// 	char *filename)
// {
// 	size_t	len;

// 	if (!filename)
// 		return (false);
// 	len = ft_strlen(filename);
// 	if (len < 4)
// 		return (false);
// 	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
// }

char	**read_map(
	const char *filename,
	t_game *game)
{
	int		fd;
	char	*line;
	int		y;

	y = 0;
	game->map = NULL;
	check_file((char *)filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit((char *)filename, ERR_OPEN_FILE);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1') //TODO : Refaire la condition
		{
			process_map_line(game, line, y);
			y++;
		}
		else
			process_config_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), game->map);
}
