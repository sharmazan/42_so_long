/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/15 18:12:05 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	i;

	s2 = malloc(ft_strlen(s) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s2[i] = (*f)(i, s[i]);
		i++;
	}
	s2[i] = 0;
	return (s2);
}

/*
int	main(void)
{
	// printf("%ld\n", ft_pow(10, 3));
	// printf("%d\n", -11 % 10);
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1000));
	printf("%s\n", ft_itoa(-123));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
	return (0);
}
*/
