/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 19:25:21 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

void	logerr(char *s)
{
	while (*s)
		write(2, s++, 1);
	write(2, "\n", 1);
}

char	**duplicate_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = ft_calloc(height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (map_free(copy), NULL);
		i++;
	}
	return (copy);
}
