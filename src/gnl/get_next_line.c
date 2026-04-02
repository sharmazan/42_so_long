/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:02:20 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/27 20:17:27 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_gnl	*get_state(void)
{
	static t_gnl	state;

	return (&state);
}

static char	*ft_realloc_str(char **src, const char *data, size_t size)
{
	char	*str;
	size_t	srclen;

	if (!*src)
		srclen = 0;
	else
		srclen = ft_strlen(*src);
	str = ft_calloc(srclen + size + 1, 1);
	if (!str)
		return (NULL);
	if (srclen)
		ft_memcpy(str, *src, srclen);
	ft_memcpy(str + srclen, data, size);
	free(*src);
	*src = str;
	return (str);
}

static char	*get_line(char **str)
{
	char	*buf;
	char	*temp;
	size_t	i;
	size_t	len;

	if (!*str)
		return (NULL);
	len = ft_strlen(*str);
	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
		i++;
	if (i == len)
		return (buf = *str, *str = NULL, buf);
	buf = ft_substr(*str, 0, i);
	temp = ft_substr(*str, i, len - i);
	if (!buf || !temp)
		return (get_state()->error = 1, free(buf), free(temp),
			free(*str), *str = NULL, NULL);
	return (free(*str), *str = temp, buf);
}

int	get_next_line_cleanup(void)
{
	t_gnl	*st;
	int		err;

	st = get_state();
	err = st->error;
	free(st->storage);
	st->storage = NULL;
	st->error = 0;
	return (err);
}

char	*get_next_line(int fd)
{
	t_gnl	*st;
	char	buf[BUFFER_SIZE + 1];
	ssize_t	br;

	st = get_state();
	st->error = 0;
	if (fd < 0)
		return (NULL);
	while (!st->storage || !ft_strchr(st->storage, '\n'))
	{
		br = read(fd, buf, BUFFER_SIZE);
		if (br == -1 || (br && !ft_realloc_str(&st->storage, buf, br)))
			return (st->error = (br != -1), free(st->storage),
				st->storage = NULL, NULL);
		if (br == 0)
			break ;
	}
	return (get_line(&st->storage));
}
