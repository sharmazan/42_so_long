/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/09 16:01:18 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_header.h"
#include <stdbool.h>

int	is_duplicates(int *a, size_t len)
{
	size_t	i;

	if (len < 2)
		return (0);
	i = 0;
	while (i++ < len - 1)
		if (a[i - 1] == a[i])
			return (1);
	return (0);
}

void	sort_array(int *a, size_t len)
{
	size_t	i;
	size_t	r;
	int		num;
	bool	swaps;

	r = len - 1;
	while (r)
	{
		i = 0;
		swaps = 0;
		while (i < r)
		{
			if (a[i] > a[i + 1])
			{
				swaps = 1;
				num = a[i + 1];
				a[i + 1] = a[i];
				a[i] = num;
			}
			i++;
		}
		if (!swaps)
			break ;
		r--;
	}
}

int	index_in_array(int n, int *a, size_t len)
{
	size_t	pos;
	size_t	l;
	size_t	r;

	pos = len / 2;
	l = 0;
	r = len;
	while (n != a[pos])
	{
		if (n < a[pos])
		{
			r = pos - 1;
			pos = (r - l) / 2;
		}
		else
		{
			l = pos + 1;
			pos = l + (r - l) / 2;
		}
		if (l > r)
			return (-1);
	}
	return (pos);
}
