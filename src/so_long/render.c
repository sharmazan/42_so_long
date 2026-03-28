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

static void	load_texture(void **img, t_game *game, char *path, char *error)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!*img)
		game_exit(game, 1, error);
	if (width != TILE_SIZE || height != TILE_SIZE)
	{
		destroy_image(game->mlx, img);
		game_exit(game, 1, "Error\nTexture size does not match TILE_SIZE");
	}
}

void	load_textures(t_game *game)
{
	load_texture(&game->floor_img, game, FLOOR_TEXTURE_PATH,
		"Error\nCould not load textures/floor.xpm");
	load_texture(&game->wall_img, game, WALL_TEXTURE_PATH,
		"Error\nCould not load textures/wall.xpm");
	load_texture(&game->player_img, game, PLAYER_TEXTURE_PATH,
		"Error\nCould not load textures/player.xpm");
	load_texture(&game->collectible_img, game, COLLECTIBLE_TEXTURE_PATH,
		"Error\nCould not load textures/collectible.xpm");
	load_texture(&game->exit_img, game, EXIT_TEXTURE_PATH,
		"Error\nCould not load textures/exit.xpm");
	load_texture(&game->open_exit_img, game, OPEN_EXIT_TEXTURE_PATH,
		"Error\nCould not load textures/open_exit.xpm");
}

void	destroy_textures(t_game *game)
{
	destroy_image(game->mlx, &game->floor_img);
	destroy_image(game->mlx, &game->wall_img);
	destroy_image(game->mlx, &game->player_img);
	destroy_image(game->mlx, &game->collectible_img);
	destroy_image(game->mlx, &game->exit_img);
	destroy_image(game->mlx, &game->open_exit_img);
}
