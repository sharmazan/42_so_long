/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/09 15:58:43 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_header.h"

char	get_bit(int pos, unsigned int c)
{
	return ((1 << pos) & c);
}

int	bits_in_number(int n)
{
	int	bits;

	bits = 0;
	while (n)
	{
		bits++;
		n >>= 1;
	}
	return (bits);
}

void	verify_int(char *s)
{
	char	*converted;
	size_t	len;

	len = ft_strlen(s);
	converted = ft_itoa(ft_atoi(s));
	if (!converted)
		errexit("malloc Error");
	if (ft_strncmp(s, converted, len + 1))
	{
		free(converted);
		errexit("Error");
	}
	free(converted);
}
