/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/15 18:10:48 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	free_array(char **arr, size_t size)
{
	while (size)
		free(arr[--size]);
	free(arr);
}

static size_t	calc_strings(char const *s, char c)
{
	size_t	chunks;

	chunks = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			chunks++;
		while (*s && *s != c)
			s++;
	}
	return (chunks);
}

static char	*copy_word(char const **s, char c)
{
	const char	*p;
	const char	*ps;

	p = *s;
	ps = *s;
	while (*ps && *ps != c)
		ps++;
	*s = ps;
	return (ft_substr(p, 0, ps - p));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;

	i = 0;
	arr = malloc((calc_strings(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		arr[i] = copy_word(&s, c);
		if (!arr[i])
			return (free_array(arr, i), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
