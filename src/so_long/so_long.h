/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:42:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/12 10:42:00 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../inc/ft_header.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_TITLE "so_long"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	*map_path;
	int		window_width;
	int		window_height;
}	t_game;

void	game_init(t_game *game, int ac, char **av);
void	game_destroy(t_game *game);
void	game_exit(t_game *game, int exit_code, char *message);
int		handle_destroy(t_game *game);
int		handle_keypress(int keysym, t_game *game);

#endif
