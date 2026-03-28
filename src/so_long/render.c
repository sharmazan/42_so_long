/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:20:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 00:20:00 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_image(void *mlx, void **img)
{
	if (mlx && *img)
	{
		mlx_destroy_image(mlx, *img);
		*img = NULL;
	}
}

static void	load_asset(void **img, t_game *game, char *path, char *name)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!*img)
		game_exit(game, 1, name);
	if (width != TILE_SIZE || height != TILE_SIZE)
	{
		destroy_image(game->mlx, img);
		game_exit(game, 1, "Error\nAsset size does not match TILE_SIZE");
	}
}

static void	*tile_image(t_game *game, char tile)
{
	if (tile == '1')
		return (game->wall_img);
	if (tile == 'C')
		return (game->collectible_img);
	if (tile == 'E')
		return (game->exit_img);
	if (tile == 'P')
		return (game->player_img);
	return (game->floor_img);
}

static void	draw_tile(t_game *game, int x, int y)
{
	void	*img;

	img = tile_image(game, game->map[y][x]);
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	load_assets(t_game *game)
{
	load_asset(&game->floor_img, game, FLOOR_PATH,
		"Error\nCould not load assets/floor.xpm");
	load_asset(&game->wall_img, game, WALL_PATH,
		"Error\nCould not load assets/wall.xpm");
	load_asset(&game->player_img, game, PLAYER_PATH,
		"Error\nCould not load assets/player.xpm");
	load_asset(&game->collectible_img, game, COLLECTIBLE_PATH,
		"Error\nCould not load assets/collectible.xpm");
	load_asset(&game->exit_img, game, EXIT_PATH,
		"Error\nCould not load assets/exit.xpm");
}

void	destroy_assets(t_game *game)
{
	destroy_image(game->mlx, &game->floor_img);
	destroy_image(game->mlx, &game->wall_img);
	destroy_image(game->mlx, &game->player_img);
	destroy_image(game->mlx, &game->collectible_img);
	destroy_image(game->mlx, &game->exit_img);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->win);
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
}

int	handle_expose(t_game *game)
{
	draw_map(game);
	return (0);
}
