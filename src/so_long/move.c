/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:45:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 14:14:46 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

static void	print_number(int number)
{
	char	digit;

	if (number >= 10)
		print_number(number / 10);
	digit = '0' + (number % 10);
	write(1, &digit, 1);
}

static void	print_moves(int moves)
{
	print_number(moves);
	write(1, "\n", 1);
}

static void	apply_move(t_game *game, int next_x, int next_y, char next_tile)
{
	if (next_tile == 'C')
		game->collected++;
	game->map[game->player_y][game->player_x] = '0';
	game->map[next_y][next_x] = 'P';
	game->player_x = next_x;
	game->player_y = next_y;
	game->moves++;
	print_moves(game->moves);
	draw_map(game);
}

void	move_player(t_game *game, int dx, int dy)
{
	int		next_x;
	int		next_y;
	char	next_tile;

	next_x = game->player_x + dx;
	next_y = game->player_y + dy;
	if (next_x < 0 || next_y < 0 || next_x >= game->map_width
		|| next_y >= game->map_height)
		return ;
	next_tile = game->map[next_y][next_x];
	if (next_tile == '1')
		return ;
	if (next_tile == 'E')
	{
		if (game->collected != game->collectibles)
			return ;
		game->moves++;
		print_moves(game->moves);
		write(1, "You Win\n", 8);
		game_exit(game, 0, NULL);
		return ;
	}
	apply_move(game, next_x, next_y, next_tile);
}
