/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/18 19:27:16 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	char	*temp;
	size_t	i;

	if (!size || !nmemb)
		return (malloc(0));
	i = nmemb * size;
	if (i / size != nmemb)
		return (NULL);
	p = malloc(i);
	if (!p)
		return (NULL);
	temp = (char *)p;
	while (i--)
		*temp++ = 0;
	return (p);
}
