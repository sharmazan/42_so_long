/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:40:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/29 14:15:07 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

static int	append_map_row(t_game *game, char *row)
{
	char	**new_map;

	new_map = ft_calloc(game->map_height + 2, sizeof(char *));
	if (!new_map)
		return (0);
	if (game->map_height > 0)
		ft_memcpy(new_map, game->map, game->map_height * sizeof(char *));
	new_map[game->map_height] = row;
	free(game->map);
	game->map = new_map;
	game->map_height++;
	return (1);
}

static int	store_map_line(t_game *game, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (append_map_row(game, line));
}

void	map_free(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	map_load(t_game *game, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		game_exit(game, 1, "Error\nCould not read map file");
	line = get_next_line(fd);
	while (line)
	{
		if (!store_map_line(game, line))
		{
			free(line);
			close(fd);
			game_exit(game, 1, "Error\nMemory allocation failed");
		}
		line = get_next_line(fd);
	}
	close(fd);
}
