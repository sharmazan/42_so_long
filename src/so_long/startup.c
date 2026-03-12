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
}

void	game_destroy(t_game *game)
{
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
	game->map_path = NULL;
	game->window_width = WINDOW_WIDTH;
	game->window_height = WINDOW_HEIGHT;
	if (ac != 2 || !has_ber_extension(av[1]))
		game_exit(game, 1, "Error: usage: ./so_long <map-file.ber>");
	game->map_path = av[1];
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(game, 1, "Error: mlx_init failed");
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, WINDOW_TITLE);
	if (!game->win)
		game_exit(game, 1, "Error: mlx_new_window failed");
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
	return (0);
}
