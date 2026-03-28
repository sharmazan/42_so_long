/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:42:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/12 10:42:00 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	has_ber_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (!ft_strncmp(path + len - 4, ".ber", 5));
}

static void	install_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, handle_keypress, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask,
		handle_destroy, game);
	mlx_expose_hook(game->win, handle_expose, game);
}

void	game_destroy(t_game *game)
{
	destroy_assets(game);
	if (game->map)
	{
		map_free(game->map);
		game->map = NULL;
	}
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	game_exit(t_game *game, int exit_code, char *message)
{
	if (message)
		logerr(message);
	game_destroy(game);
	exit(exit_code);
}

void	game_init(t_game *game, int ac, char **av)
{
	game->mlx = NULL;
	game->win = NULL;
	game->floor_img = NULL;
	game->wall_img = NULL;
	game->player_img = NULL;
	game->collectible_img = NULL;
	game->exit_img = NULL;
	game->map_path = NULL;
	game->map = NULL;
	game->window_width = 0;
	game->window_height = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->exits = 0;
	game->moves = 0;
	if (ac != 2 || !has_ber_extension(av[1]))
		game_exit(game, 1, "Error\nusage: ./so_long <map-file.ber>");
	game->map_path = av[1];
	map_load(game, game->map_path);
	map_validate(game);
	game->window_width = game->map_width * TILE_SIZE;
	game->window_height = game->map_height * TILE_SIZE;
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(game, 1, "Error\nmlx_init failed");
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, WINDOW_TITLE);
	if (!game->win)
		game_exit(game, 1, "Error\nmlx_new_window failed");
	load_assets(game);
	draw_map(game);
	install_hooks(game);
}

int	handle_destroy(t_game *game)
{
	game_exit(game, 0, NULL);
	return (0);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		game_exit(game, 0, NULL);
	else if (keysym == XK_w || keysym == XK_W)
		move_player(game, 0, -1);
	else if (keysym == XK_a || keysym == XK_A)
		move_player(game, -1, 0);
	else if (keysym == XK_s || keysym == XK_S)
		move_player(game, 0, 1);
	else if (keysym == XK_d || keysym == XK_D)
		move_player(game, 1, 0);
	return (0);
}
