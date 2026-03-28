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

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define TILE_SIZE 64
# define WINDOW_TITLE "so_long"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	*map_path;
	char	**map;
	int		window_width;
	int		window_height;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		collected;
	int		exits;
	int		moves;
}	t_game;

void	game_init(t_game *game, int ac, char **av);
void	game_destroy(t_game *game);
void	game_exit(t_game *game, int exit_code, char *message);
void	logerr(char *s);
void	map_load(t_game *game, char *path);
void	map_validate(t_game *game);
void	map_validate_path(t_game *game);
void	map_free(char **map);
int		handle_destroy(t_game *game);
int		handle_keypress(int keysym, t_game *game);

#endif
