/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:12:52 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/23 12:46:44 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	_ft_print_d(long n)
{
	if (n >= 10)
		return (ft_print_d(n / 10) + ft_print_d(n % 10));
	return (ft_print_c(n + 48));
}

int	ft_print_d(int n)
{
	long	_n;

	_n = n;
	if (n < 0)
		return (write(STDOUT_FILENO, "-", 1) + _ft_print_d(-_n));
	return (_ft_print_d(_n));
}
