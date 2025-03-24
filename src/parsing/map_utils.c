/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:11:06 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/11 08:21:07 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

bool	is_cub_file(
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

static bool	is_dir(
	char *filename
)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd >= 0)
		return (close(fd), true);
	return (false);
}

bool	check_file(
	char *filename)
{
	if (is_dir(filename))
		error_exit(filename, ERR_FILE_IS_DIR);
	if (!is_cub_file(filename))
		error_exit(filename, ERR_FILE_NOT_CUB);
	return (true);
}
