/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/02 16:17:28 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	digit;

	sign = 1;
	i = 0;
	while (is_space(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	while (*nptr == '0')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
		i = i * 10 + digit;
		nptr++;
	}
	return (i * sign);
}
