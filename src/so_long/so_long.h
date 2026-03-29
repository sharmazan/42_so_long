/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:42:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 19:25:38 by ssharmaz         ###   ########.fr       */
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
# define FLOOR_TEXTURE_PATH "textures/floor.xpm"
# define WALL_TEXTURE_PATH "textures/wall.xpm"
# define PLAYER_TEXTURE_PATH "textures/player.xpm"
# define COLLECTIBLE_TEXTURE_PATH "textures/collectible.xpm"
# define EXIT_TEXTURE_PATH "textures/exit.xpm"
# define OPEN_EXIT_TEXTURE_PATH "textures/open_exit.xpm"

typedef struct s_game
{
	void	*mlx;
	void	*window;
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	void	*collectible_img;
	void	*exit_img;
	void	*open_exit_img;
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
void	install_hooks(t_game *game);
void	load_textures(t_game *game);
void	destroy_textures(t_game *game);
int		draw_map(t_game *game);
void	logerr(char *s);
char	**duplicate_map(char **map, int height);
void	move_player(t_game *game, int dx, int dy);
void	map_load(t_game *game, char *path);
void	map_validate(t_game *game);
void	map_validate_path(t_game *game);
void	map_free(char **map);
int		handle_destroy(t_game *game);
int		handle_keypress(int keysym, t_game *game);

#endif
