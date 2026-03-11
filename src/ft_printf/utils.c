/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/11/04 19:17:18 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	printed;

	if (!s)
		s = "(null)";
	printed = 0;
	while (*s)
		printed += write(fd, s++, 1);
	return (printed);
}

int	ft_putnum_base(size_t n, char *base, int fd)
{
	int		digit;
	int		ibase;
	int		i;
	char	buf[255];
	int		printed;

	if (!base || *base == 0)
		return (0);
	if (n == 0)
		return (write(fd, base, 1));
	ibase = 0;
	while (base[ibase])
		ibase++;
	printed = 0;
	i = 0;
	while (n > 0)
	{
		digit = n % ibase;
		buf[i++] = *(base + digit);
		n /= ibase;
	}
	while (i > 0)
		printed += write(fd, &buf[--i], 1);
	return (printed);
}
