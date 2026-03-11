/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/14 20:28:40 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

static int	is_str_in(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1) == (*s2))
	{
		s1++;
		s2++;
	}
	if (*s2 == 0)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	littlesize;
	char	*p;

	i = 0;
	p = (char *)big;
	if (*little == '\0')
		return (p);
	littlesize = ft_strlen(little);
	while (p[i] && len - i >= littlesize)
	{
		if (is_str_in(&p[i], little))
			return (&p[i]);
		i++;
	}
	return (NULL);
}
