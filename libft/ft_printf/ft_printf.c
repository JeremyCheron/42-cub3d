/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:45:35 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/23 12:46:22 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_formats(va_list args, const char format)
{
	if (format == 'c')
		return (ft_print_c(va_arg(args, int)));
	if (format == 's')
		return (ft_print_s(va_arg(args, char *)));
	if (format == 'd' || format == 'i')
		return (ft_print_d(va_arg(args, int)));
	if (format == '%')
		return (ft_print_c('%'));
	if (format == 'x' || format == 'X')
		return (ft_print_x(va_arg(args, unsigned int), format));
	if (format == 'p')
		return (ft_print_p(va_arg(args, uintptr_t)));
	if (format == 'u')
		return (ft_print_u(va_arg(args, unsigned int)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			len += write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
