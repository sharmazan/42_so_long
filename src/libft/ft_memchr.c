/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/14 20:56:35 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*p;
	size_t	i;

	if (n == 0)
		return (NULL);
	i = 0;
	p = (char *)s;
	while (i++ < n)
	{
		if (*p == (signed char)c)
			return (p);
		p++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s[] = {0, 1, 2, 3, 4, 5};
	char	*src;
	int		size;

	if (ft_memchr(s, 0, 0) == memchr(s, 0, 0))
		printf("1 passed\n");
	if (ft_memchr(s, 0, 1) == memchr(s, 0, 1))
		printf("2 passed\n");
	if (ft_memchr(s, 2, 3) == memchr(s, 2, 3))
		printf("3 passed\n");
	if (ft_memchr(s, 6, 6) == memchr(s, 6, 6))
		printf("4 passed\n");
	if (ft_memchr(s, 2 + 256, 3) == memchr(s, 2 + 256, 3))
		printf("5 passed\n");
	src = "/|\x12\xff\x09\x42\2002\42|\\";
	size = 10;
	if (memchr(src, '\200', size) == ft_memchr(src, '\200', size))
		printf("6 passed\n");
	return (0);
}
*/
