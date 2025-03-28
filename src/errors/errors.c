/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:23:50 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/11 08:15:28 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	error_exit(
	char *arg,
	char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" ", 2);
	ft_putendl_fd(message, 2);
	exit(1);
}
