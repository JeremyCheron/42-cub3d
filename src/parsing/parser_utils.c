/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 08:18:28 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/24 12:09:51 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

bool	is_valid_texture(char *texture)
{
	int	fd;

	fd = open(texture, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

bool	parse_rgb_value(char **color, int *value)
{
	*value = 0;
	while (ft_iswhitespace(**color))
		(*color)++;
	if (!ft_isdigit(**color))
		return (false);
	while (ft_isdigit(**color))
	{
		*value = *value * 10 + (**color - '0');
		(*color)++;
	}
	return (*value >= 0 && *value <= 255);
}

bool	is_valid_color(char *color)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (i < 3)
	{
		if (!parse_rgb_value(&color, &rgb[i]))
			return (false);
		if (i < 2)
		{
			while (ft_iswhitespace(*color))
				color++;
			if (*color != ',')
				return (false);
			color++;
		}
		i++;
	}
	while (ft_iswhitespace(*color))
		color++;
	if (*color != '\0')
		return (false);
	return (true);
}

bool	is_config_line(char *line, t_game *game)
{
	char	**split;
	bool	valid;

	if (line[0] == '\n')
		return (false);
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		ft_free_split(split);
		free(line);
		clear_config(&game->config);
		error_exit("ERROR: ", "Invalid line");
	}
	valid = false;
	if (!ft_strncmp(split[0], "NO", 3) || !ft_strncmp(split[0], "SO", 3)
		|| !ft_strncmp(split[0], "WE", 3) || !ft_strncmp(split[0], "EA", 3))
		valid = true;
	else if (!ft_strncmp(split[0], "F", 2) || !ft_strncmp(split[0], "C", 2))
		valid = true;
	ft_free_split(split);
	return (valid);
}
