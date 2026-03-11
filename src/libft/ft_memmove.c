/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/14 20:41:11 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ps;
	char	*pd;

	ps = (char *)src;
	pd = (char *)dest;
	if (pd < ps)
		while (n--)
			*pd++ = *ps++;
	else
	{
		ps = ps + n - 1;
		pd = pd + n - 1;
		while (n--)
			*pd-- = *ps--;
	}
	return (dest);
}
