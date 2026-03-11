/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_int_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/12 18:23:18 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int	*num;

	num = malloc(sizeof(int));
	*num = 2;
	printf("%d\n", *num);
	printf("%d\n", (int *)num);
	return (0);
}
