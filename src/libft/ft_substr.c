/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/14 19:28:41 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

	i = 0;
	while (s[i] && i < start)
		i++;
	if (!s[i] || len == 0)
		return (ft_strdup(""));
	s += i;
	i = 0;
	while (s[i] && i < len)
		i++;
	newstr = malloc((i + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s, i + 1);
	return (newstr);
}
/*
int	main(void)
{
	printf("%s\n", ft_substr("i just want this part #############", 2, 4));
	return (0);
}
	i = 0;
	while (*p && p < s && i < len)
		newstr[i++] = *p++;
	newstr[i] = '\0';

*/
