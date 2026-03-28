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

static void	init_game_state(t_game *game)
{
	ft_bzero(game, sizeof(*game));
}

static void	init_graphics(t_game *game)
{
	game->window_width = game->map_width * TILE_SIZE;
	game->window_height = game->map_height * TILE_SIZE;
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(game, 1, "Error\nmlx_init failed");
	game->window = mlx_new_window(game->mlx, game->window_width,
			game->window_height, WINDOW_TITLE);
	if (!game->window)
		game_exit(game, 1, "Error\nmlx_new_window failed");
	load_textures(game);
	draw_map(game);
	install_hooks(game);
}

void	game_init(t_game *game, int ac, char **av)
{
	init_game_state(game);
	if (ac != 2 || !has_ber_extension(av[1]))
		game_exit(game, 1, "Error\nusage: ./so_long <map-file.ber>");
	map_load(game, av[1]);
	map_validate(game);
	init_graphics(game);
}
