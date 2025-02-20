/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 08:35:47 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/23 12:46:47 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

#define NIL_STR "(nil)"
#define ADDR_STR "0x"

static int	_ft_print_p(uintptr_t ptr)
{
	if (ptr >= 16)
		return (_ft_print_p(ptr / 16) + _ft_print_p(ptr % 16));
	return (ft_print_c(LOWERX[ptr]));
}

int	ft_print_p(uintptr_t ptr)
{
	if (!ptr)
		return (ft_print_s(NIL_STR));
	if (ft_print_s(ADDR_STR) < 0)
		return (-1);
	return (_ft_print_p(ptr) + 2);
}
