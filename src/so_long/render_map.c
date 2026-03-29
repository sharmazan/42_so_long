/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:20:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 14:14:07 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*tile_image(t_game *game, char tile)
{
	if (tile == '1')
		return (game->wall_img);
	if (tile == 'C')
		return (game->collectible_img);
	if (tile == 'E')
	{
		if (game->collected == game->collectibles)
			return (game->open_exit_img);
		return (game->exit_img);
	}
	if (tile == 'P')
		return (game->player_img);
	return (game->floor_img);
}

static void	draw_tile(t_game *game, int x, int y)
{
	void	*img;

	img = tile_image(game, game->map[y][x]);
	mlx_put_image_to_window(game->mlx, game->window, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

int	draw_map(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->window);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
