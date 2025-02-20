/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:24:24 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/23 12:24:49 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*s;
	char		*d;

	if (!src && !dest)
		return (NULL);
	s = (char *)src;
	d = (char *)dest;
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		ft_memcpy(dest, s, len);
	}
	return (dest);
}
