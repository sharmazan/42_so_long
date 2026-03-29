/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_verification.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:40:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 19:27:01 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill_without_exit(char **map, int x, int y, t_game *game)
{
	if (x <= 0 || y <= 0 || x >= game->map_width || y >= game->map_height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'E')
		return ;
	map[y][x] = 'F';
	flood_fill_without_exit(map, x + 1, y, game);
	flood_fill_without_exit(map, x - 1, y, game);
	flood_fill_without_exit(map, x, y + 1, game);
	flood_fill_without_exit(map, x, y - 1, game);
}

static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x <= 0 || y <= 0 || x >= game->map_width || y >= game->map_height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

static void	check_reachable_collectibles(t_game *game, char **copy)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (copy[y][x] == 'C')
			{
				map_free(copy);
				game_exit(game, 1,
					"Error\nMap must allow access to all "
					"collectibles before reaching the exit");
			}
			x++;
		}
		y++;
	}
}

static void	check_reachable_exit(t_game *game, char **copy)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (copy[y][x] == 'E')
			{
				map_free(copy);
				game_exit(game, 1,
					"Error\nMap must allow access to the exit");
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
	flood_fill_without_exit(copy, game->player_x, game->player_y, game);
	check_reachable_collectibles(game, copy);
	map_free(copy);
	copy = duplicate_map(game->map, game->map_height);
	if (!copy)
		game_exit(game, 1, "Error\nMemory allocation failed");
	flood_fill(copy, game->player_x, game->player_y, game);
	check_reachable_exit(game, copy);
	map_free(copy);
}
