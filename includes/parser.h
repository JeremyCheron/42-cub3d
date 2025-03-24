/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:14:15 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/13 08:12:38 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SOUTH "SO"
# define NORTH "NO"
# define EAST "EA"
# define WEST "WE"
# define FLOOR "F"
# define CEILING "C"

// char	**read_map(
// 			const char *filename);

bool	check_file(
			char *filename);

#endif
