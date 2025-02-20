/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:41:45 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/20 17:55:13 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static bool	_is_cub_file(
	char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

char	**read_map(
	const char *filename)
{
	int		fd;
	char	*line;
	char	**map;

	(void)map;
	if (!_is_cub_file((char *)filename))
		error_exit("Invalid file extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (NULL);
}
