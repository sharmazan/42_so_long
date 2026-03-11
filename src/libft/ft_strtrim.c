/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/14 20:59:44 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*new;
	const char	*end;

	if (*s1 == 0)
		return (ft_strdup(""));
	end = s1 + ft_strlen(s1) - 1;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (*s1 == 0)
		return (ft_strdup(""));
	while (end > s1 && ft_strchr(set, *end))
		end--;
	new = ft_substr(s1, 0, end - s1 + 1);
	return (new);
}
