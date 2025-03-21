/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:59:20 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/21 07:58:11 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	set_texture(char **texture, char *line)
{
	char	**split;
	int		len;

	split = ft_split(line + 2, ' ');
	if (!split)
		return (-1);
	if (!split || split[1])
		return (ft_free_split(split), -1);
	len = ft_strlen(split[0]);
	if (len > 0 && split[0][len - 1] == '\n')
		split[0][len - 1] = '\0';
	*texture = ft_strdup(split[0]);
	ft_free_split(split);
	return (0);
}

int	parse_color(char *line, int color[3])
{
	char	**split;

	split = ft_split(line + 2, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (-1);
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	ft_free_split(split);
	if (color[0] < 0 || color[0] > 255
		|| color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (-1);
	return (0);
}

char	**append_line_to_map(char **map, char *line)
{
	int		i;
	char	**new_map;

	i = 0;
	if (map)
	{
		while (map[i])
			i++;
	}
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	if (map)
	{
		while (map[i])
		{
			new_map[i] = map[i];
			i++;
		}
	}
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

int	parse_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_isdigit(line[0]))
			process_map_line(game, line, y++);
		else
			process_config_line(game, line);
		free(line);
	}
	close(fd);
	return (0);
}
