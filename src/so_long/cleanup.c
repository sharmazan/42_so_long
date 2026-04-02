/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:20:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 14:15:21 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_destroy(t_game *game)
{
	get_next_line_cleanup();
	if (game->map)
	{
		map_free(game->map);
		game->map = NULL;
	}
	destroy_textures(game);
	if (game->mlx && game->window)
	{
		mlx_destroy_window(game->mlx, game->window);
		game->window = NULL;
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
