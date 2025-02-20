/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:55:42 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/23 12:25:43 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	l_len;

	l_len = ft_strlen(needle);
	if (!l_len)
		return ((char *)haystack);
	while (*haystack && l_len <= len--)
	{
		if (!ft_memcmp(haystack, needle, l_len))
			return ((char *)haystack);
		haystack++;
	}
	return (0);
}
