/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:30:17 by jcheron           #+#    #+#             */
/*   Updated: 2024/12/23 13:35:15 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// size_t	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

void	ft_fill(char *filled, char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1[j])
		filled[i++] = s1[j++];
	j = 0;
	while (s2[j])
		filled[i++] = s2[j++];
	filled[i] = '\0';
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*joined;

// 	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!joined)
// 		return (NULL);
// 	ft_fill(joined, s1, s2);
// 	return (joined);
// }

// char	*ft_strdup(char *s1)
// {
// 	unsigned int	i;
// 	char			*dupe;

// 	dupe = (char *)malloc(ft_strlen(s1) + 1);
// 	if (!dupe)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		dupe[i] = s1[i];
// 		i++;
// 	}
// 	dupe[i] = '\0';
// 	return (dupe);
// }

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	char	*str;

// 	if (!s)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 		return (malloc(1));
// 	if (len > ft_strlen(s + start))
// 		len = ft_strlen(s + start);
// 	str = malloc((len + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = s[start + i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }
