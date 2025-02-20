/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:08:45 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/23 13:34:41 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	_ft_print_x(unsigned int n, char *chars)
{
	if (n >= 16)
		return (_ft_print_x(n / 16, chars) + _ft_print_x(n % 16, chars));
	return (ft_print_c(chars[n]));
}

int	ft_print_x(unsigned int n, int format)
{
	if (format == 'x')
		return (_ft_print_x(n, LOWERX));
	return (_ft_print_x(n, UPPERX));
}
