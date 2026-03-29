/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:40:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 18:50:21 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_tile(char tile)
{
	return (tile == '0' || tile == '1' || tile == 'C'
		|| tile == 'E' || tile == 'P');
}

static void	register_tile(t_game *game, int *players, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	if (tile == 'P')
	{
		(*players)++;
		game->player_x = x;
		game->player_y = y;
	}
	else if (tile == 'C')
		game->collectibles++;
	else if (tile == 'E')
		game->exits++;
}

static void	validate_rows(t_game *game, int *players)
{
	int		x;
	int		y;
	size_t	row_len;

	y = 0;
	while (game->map[y])
	{
		row_len = ft_strlen(game->map[y]);
		if ((int)row_len != game->map_width)
			game_exit(game, 1, "Error\nMap must be rectangular");
		x = 0;
		while (game->map[y][x])
		{
			if (!is_valid_tile(game->map[y][x]))
				game_exit(game, 1, "Error\nMap contains invalid characters");
			if ((y == 0 || y == game->map_height - 1 || x == 0
					|| x == game->map_width - 1) && game->map[y][x] != '1')
				game_exit(game, 1, "Error\nMap must be closed by walls");
			register_tile(game, players, x, y);
			x++;
		}
		y++;
	}
}

static void	validate_counts(t_game *game, int players)
{
	if (players != 1)
		game_exit(game, 1, "Error\nMap must contain exactly one player");
	if (game->exits != 1)
		game_exit(game, 1, "Error\nMap must contain exactly one exit");
	if (game->collectibles < 1)
		game_exit(game, 1, "Error\nMap must contain at least one collectible");
}

void	map_validate(t_game *game)
{
	int	players;

	if (!game->map_height || !game->map || !game->map[0])
		game_exit(game, 1, "Error\nMap file is empty");
	game->map_width = ft_strlen(game->map[0]);
	if (game->map_width == 0)
		game_exit(game, 1, "Error\nMap contains an empty row");
	game->collectibles = 0;
	game->collected = 0;
	game->exits = 0;
	game->moves = 0;
	players = 0;
	validate_rows(game, &players);
	validate_counts(game, players);
	map_validate_path(game);
}
