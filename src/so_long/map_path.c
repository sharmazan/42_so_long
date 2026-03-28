/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:40:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/28 22:40:00 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**duplicate_map(char **map, int height)
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

static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

static void	check_reachable_tiles(t_game *game, char **copy)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (copy[y][x] == 'C' || copy[y][x] == 'E')
			{
				map_free(copy);
				game_exit(game, 1,
					"Error\nMap must allow access to all "
					"collectibles and exit");
			}
			x++;
		}
		y++;
	}
}

void	map_validate_path(t_game *game)
{
	char	**copy;

	copy = duplicate_map(game->map, game->map_height);
	if (!copy)
		game_exit(game, 1, "Error\nMemory allocation failed");
	flood_fill(copy, game->player_x, game->player_y, game);
	check_reachable_tiles(game, copy);
	map_free(copy);
}
