/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:37:05 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/29 15:40:52 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_isnumber(const char *str)
{
	while (*str && ft_iswhitespace((unsigned char)*str))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0' || !ft_isdigit((unsigned char)*str))
		return (0);
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}
