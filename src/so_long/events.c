/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:20:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 00:20:00 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	install_hooks(t_game *game)
{
	mlx_hook(game->window, KeyPress, KeyPressMask, handle_keypress, game);
	mlx_hook(game->window, DestroyNotify, StructureNotifyMask,
		handle_destroy, game);
	mlx_expose_hook(game->window, draw_map, game);
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
