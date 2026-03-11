/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/02 20:49:57 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	get_bit(int pos, unsigned char c)
{
	if (((1 << pos) & c) > 0)
		return (1);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	int		num;
// 	char	*s;

// 	if (ac == 1)
// 	{
// 		for (int i = 0; i < 8; i++)
// 			printf("%d\n", 1 << i);
// 	}
// 	num = atoi(av[1]);
// 	for (int i = 0; i < 8; i++)
// 		printf("%d\n", (1 << i) & num);
// 	printf("\n*****************************\n");
// 	for (int i = 0; i < 8; i++)
// 		printf("%d", get_bit(i, num));
// 	printf("\n*****************************\n");
// 	printf("1 << 0 = %d, 1 << 2 = %d, 1 | 1 << 2 = %d\n", 1 << 0, 1 << 2,
// 		1 | 1 << 2);
// 	printf("*****************************\n");
// 	printf("Testing UNICODE\n");
// 	s = "🤨🤨🤨🤨🤨🤨🤨";
// 	printf("Len: %lu\n", strlen(s));
// 	while (*s != '\0')
// 		printf("%c\n", *s++);
// 	s = "🤨🤨🤨🤨🤨🤨🤨";
// 	printf("Len: %lu\n", strlen(s));
// 	printf("%s\n", s);
// 	s = "🤨🤨🤨🤨🤨🤨🤨";
// 	printf("Len: %lu\n", strlen(s));
// 	while (*s != '\0')
// 		write(1, s++, 1);
// 	return (0);
// }
